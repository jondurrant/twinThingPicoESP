/*
 * WifiAgent.cpp
 *
 *  Created on: 24 Nov 2021
 *      Author: jondurrant
 */

#include "WifiHelper.h"

#include "lwesp/lwesp.h"

WifiHelper::WifiHelper() {
	// TODO Auto-generated constructor stub

}



WifiHelper::~WifiHelper() {
	// TODO Auto-generated destructor stub
}


bool WifiHelper::connectToAp(const char * sid, const char *passwd){
	lwespr_t eres;
	char ipStr[16];

	/* Initialize ESP with default callback function */
	//LogInfo(("Initializing LwESP"));
	printf("Initializing LwESP\r\n");

	if (lwesp_init(NULL, 1) != lwespOK) {
		printf("Cannot initialize LwESP!\r\n");

	} else {
		printf("LwESP initialized!\r\n");


		if (lwesp_sta_has_ip()) {
			printf("Already connected\r\n");
			lwesp_ip_t ip;
			uint8_t is_dhcp;

			lwesp_sta_copy_ip(&ip, NULL, NULL, &is_dhcp);
			/*
			ip2str(ipStr, &ip);
			printf("Station IP address: %s\r\n", ipStr);
			printf("; Is DHCP: %d\r\n", (int)is_dhcp);
			*/



		} else {
			if (lwesp_sta_join(sid, passwd, NULL, NULL, NULL, 1) == lwespOK) {
				 lwesp_ip_t ip;
				 uint8_t is_dhcp;

				 printf("Connected to %s network!\r\n", sid);
				 /*
				 lwesp_sta_copy_ip(&ip, NULL, NULL, &is_dhcp);

				 ip2str(ipStr, &ip);
				 printf("Station IP address: %s\r\n", ipStr);
				 printf("; Is DHCP: %d\r\n", (int)is_dhcp);
				 */

			 } else {
				 printf("Connection error: %d\r\n", (int)eres);
				 return false;
			 }
		}
		return true;
	}
	return false;
}

