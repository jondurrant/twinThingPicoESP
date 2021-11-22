/*
 * StateTask.cpp
 *
 *  Created on: 22 Nov 2021
 *      Author: jondurrant
 */

#include "TwinTask.h"
#include <cstring>

TwinTask::TwinTask() {
	// TODO Auto-generated constructor stub

}

TwinTask::~TwinTask() {
	stop();
	if (updateTopic != NULL){
		vPortFree(updateTopic);
		updateTopic = NULL;
	}
}


void TwinTask::setStateObject(State *state){
	pState = state;
	pState->attach(this);
}


void TwinTask::setMQTTInterface(MQTTInterface *mi){
	mqttInterface = mi;
	if (updateTopic == NULL){
		updateTopic = (char *)pvPortMalloc(
				MQTTTopicHelper::legThingUpdate(mi->getId())
				);
		if (updateTopic != NULL){
			MQTTTopicHelper::getThingUpdate(updateTopic, this->getId());
		} else {
			LogError( ("Allocated failed") );
		}
	}
}

void TwinTask::addMessage(char * msg, size_t msgLen){
	if (xMessageBuffer != NULL){
		size_t res = xMessageBufferSend(xMessageBuffer,
					msg, msgLen, 0 );
			if (res != payloadLen){
				LogError( ("addMessage failed\n") );
				return false;
			}
	} else {
		LogError( ("No Message Buf") );
		return false;
	}
	return true;
}

/***
 *  create the vtask, will get picked up by scheduler
 *
 *  */
void TwinTask::start(UBaseType_t priority = tskIDLE_PRIORITY){
	xMessageBuffer = xMessageBufferCreate( STATE_MSG_BUF_LEN );
	if (xMessageBuffer == NULL){
		LogError( ("Create buf failed") );
		return;
	}
	if (xMessageBuffer != NULL){
		xTaskCreate(
			TwinTask::vTask,
			"MQTTstate",
			512,
			( void * ) this,
			priority,
			&xHandle
		);
	}
}

/***
 * Stop the vtask
 */
void TwinTask::stop(){
	if (xHandle != NULL){
		vTaskDelete(  xHandle );
		xHandle = NULL;
	}

	if (xMessageBuffer != NULL){
		vMessageBufferDelete(xMessageBuffer);
		xMessageBuffer = NULL;
	}
}


/***
 * Internal function used by FreeRTOS to run the task
 * @param pvParameters
 */
void TwinTask::vTask( void * pvParameters ){
	TwinTask *task = (TwinTask *) pvParameters;
	task->run();
}

/***
 * Internal function to run the task from within the object
 */
void TwinTask::run(){

	for (;;){
		if (xMessageBufferIsEmpty(xMessageBuffer) == pdTRUE){
			taskYIELD();
		} else {
			vTaskDelay( 20 );
			size_t size = xMessageBufferReceive(xMessageBuffer,
								xMsg, STATE_MAX_MSG_LEN, 0);
			if (size > 0){
				if (pState != NULL){
					processJson(msg);
				}
			}
		}
	}
}


/***
* Process a json message received
* @param str
*/
void TwinTask::processJson(char *str){
	json_t const* json = json_create( str, jsonBuf, jsonBufLen );
	if ( !json ) {
		LogError( ("json create. %s",str) );
		return;
	}

	json_t const* delta = json_getProperty(json, TWINDELTA);
	if (!delta){
		delta = json_getProperty(json, TWINSTATE);
	}

	if (delta){
		pState->startTransaction();
		pState->updateFromJson(delta);
		pState->commitTransaction();
	}
}

/***
 * Notification of a change of a state item with the State object.
 * @param dirtyCode - Representation of item changed within state. Used to pull back delta
 */
void notifyState(unsigned char dirtyCode){
	if (mqttInterface != NULL){
		unsigned int i;

		i = pState->delta(xMsg, STATE_MAX_MSG_LEN, dirtyCode);
		if (i == 0){
			LogError(("Buf overrun"));
		}
		mqttInterface->pubToTopic(updateTopic, xMsg, strLen(xMsg));
	}
}
