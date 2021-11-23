/*
 * MQTTRouterTwin.h
 *
 * Route state messages to the twin
 *
 *  Created on: 23 Nov 2021
 *      Author: jondurrant
 */

#ifndef SRC_MQTTROUTERTWIN_H_
#define SRC_MQTTROUTERTWIN_H_

#include "MQTTConfig.h"
#include "MQTTRouterPing.h"
#include "TwinTask.h"
#include "State.h"

class MQTTRouterTwin : public MQTTRouterPing {
public:
	MQTTRouterTwin();
	virtual ~MQTTRouterTwin();

	MQTTRouterTwin(const char * id, MQTTInterface *mi, State *state);

	/***
	 * Initialise the object give the Id and MQTT Interface
	 * @param id = string ID of the Thing
	 * @param mi = MQTT Interface
	 */
	virtual void init(const char * id, MQTTInterface *mi, State * state);

	/***
	 * Use the interface to setup all the subscriptions
	 * @param interface
	 */
	virtual void subscribe(MQTTInterface *interface);

	/***
	 * Route the message the appropriate part of the application
	 * @param topic
	 * @param topicLen
	 * @param payload
	 * @param payloadLen
	 * @param interface
	 */
	virtual void route(const char *topic, size_t topicLen, const void * payload,
			size_t payloadLen, MQTTInterface *interface);

private:
	TwinTask xTwin;

	char * pSetTopic = NULL;
	char * pGetTopic = NULL;

};

#endif /* SRC_MQTTROUTERTWIN_H_ */
