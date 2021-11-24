/*
 * WifiAgent.h
 *
 *  Created on: 24 Nov 2021
 *      Author: jondurrant
 */

#ifndef SRC_WIFIHELPER_H_
#define SRC_WIFIHELPER_H_

#include "MQTTConfig.h"
#include <stdlib.h>

class WifiHelper {
public:
	WifiHelper();

	virtual ~WifiHelper();

	static bool connectToAp(const char * sid, const char *passwd);

private:

};

#endif /* SRC_WIFIHELPER_H_ */
