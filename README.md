# twinThingPicoESP

Raspberry Pi PICO or RP2040 as IoT device using [ESP-01S](https://behind-the-scenes.net/introducing-the-inexpensive-esp-01-wi-fi-module/) for Wifi access.

Example code using the library can be found in  [twinThingPicoESPExample](https://github.com/jondurrant/twinThingPicoESPExample). 

## IOT
Library connects RP2040 to MQTT hub as a client which can publish and subscribe to topics. 

Structures

TNG/<ID>/ - THING / ID, same as user name in my example
TNG/<ID>/LC - LC is lifecycle and annouces connection and disconnection
TNG/<ID>/TPC - TOPIC, for messaging to a specific thing

Example assuming you name the pico as "pico"
+ TNG/pico/TPC/PING - ping re	quest sent to pico
+ TNG/pico/TPC/PONG - pong as response to the ping

Group topics also exist in the structure under.

GRP/<Group>/TPC/ - Topics to talk to group of devices

Examle:
GRP/ALL/TPC/PING - ping topic that all IoT devices listen for.

Tested against:
+ [Mosquitto](https://mosquitto.org/) on a RPI4. Followed the docker install guide at: (https://docs.cedalo.com/streamsheets/2.4/installation/)
+ [EMQX](https://www.emqx.io/) 

# Hardware
+ Raspberry Pico
+ ESP-01S (1Mb) running ESP-AT 2.1

## Connections:
PICO Uart0 on GPIO12 and 13

|pico|function|ESP-01S| function|
|----|--------|-------|---------|
|G12 | TX     | RX    | RX      |
|G13 | RX     | TX    | TX      |
|3.3 | 3.3v   | 3.3   | 3.3v    |
|GND |GND     | GND   | GND     |
|3.3 | 3.3v   | EN    | via 10k res|


## ESP-01S
I got very cheap pack of ESP-01S but they came with 1Mb flash. Latest version of ESP-AT, version 2.2, requires 2MB. 

Fortunatly Jandrassy has built a working 2.1 firmware for 1MB. This is on github at: https://github.com/jandrassy/WiFiEspAT

To reliably upload the firmware to ESP-01S requires the RST IO0 to get pulled to zero and the released. Some further inform on how to do this at: https://blog.tiga.tech/flashing-esphome-firmware-to-esp-01s/

I used the RPI 4 to upload the firmware and the esptool.py. I had to drop frequency to 40m and change upload mode to dout in the download.config file. Then use the command
esptool.py --port /dev/ttyS0 write_flash @download.config

# Dependencies
## C++
+ [lwesp](https://github.com/MaJerle/lwesp): library for talking to ESP-AT over serial
+ + [forkedlwesp](https://github.com/jondurrant/lwespFork) Forked to allow MQTT over SSL. 
+ [FreeRTOS-Kernel](https://github.com/FreeRTOS/FreeRTOS-Kernel): dependency for lwesp
+ [json-maker](https://github.com/rafagafe/json-maker)
+ [tiny-json](https://github.com/rafagafe/tiny-json)

# Build
See example usage: [twinThingPicoESPExample](https://github.com/jondurrant/twinThingPicoESPExample).

Cmake variable to point to config file director where it will include MQTTConfig.h

example:
set(TWIN_THING_PICO_CONFIG_PATH ${CMAKE_CURRENT_LIST_DIR}/src/config)