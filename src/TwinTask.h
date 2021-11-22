/*
 * StateTask.h
 * Task to manage state updates for publishing and processing of MQTT
 *
 *  Created on: 22 Nov 2021
 *      Author: jondurrant
 */

#ifndef SRC_TWINTASK_H_
#define SRC_TWINTASK_H_

#include "State.h"
#include "MQTTInterface.h"
#include "MQTTConfig.h"
#include "StateObserver.h"
#include <FreeRTOS.h>
#include <message_buffer.h>
#include <stdlib.h>
#include "tiny-json.h"

#ifndef STATE_MSG_BUF_LEN
#define STATE_MSG_BUF_LEN 512
#endif
#ifndef STATE_MAX_MSG_LEN
#define STATE_MAX_MSG_LEN 100
#endif

class TwinTask : public StateObserver {
public:
	TwinTask();
	virtual ~TwinTask();

	void setStateObject(State *state);
	void setMQTTInterface(MQTTInterface *mi);
	bool addMessage(char * msg, size_t msgLen);

	/***
	 *  create the vtask, will get picked up by scheduler
	 *
	 *  */
	void start(UBaseType_t priority = tskIDLE_PRIORITY);

	/***
	 * Stop the vtask
	 */
	void stop();

	/***
	 * Notification of a change of a state item with the State object.
	 * @param dirtyCode - Representation of item changed within state. Used to pull back delta
	 */
	virtual void notifyState(unsigned char dirtyCode);


private:
	/***
	 * Internal function used by FreeRTOS to run the task
	 * @param pvParameters
	 */
	static void vTask( void * pvParameters );

	/***
	 * Internal function to run the task from within the object
	 */
	void run();

	/***
	* Process a json message received
	* @param str
	*/
	void processJson(char *str);


	MessageBufferHandle_t xMessageBuffer = NULL;
	MQTTInterface *mqttInterface = NULL;
	TaskHandle_t xHandle = NULL;


	State * pState = NULL;

	char xMsg[STATE_MAX_MSG_LEN];
	char * updateTopic = NULL;

	//Json parsing structure buffer
	json_t *jsonBuf = NULL;
	unsigned int jsonBufLen = 0;
};

#endif /* SRC_TWINTASK_H_ */
