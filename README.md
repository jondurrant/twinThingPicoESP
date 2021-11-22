# twinThingPicoESP


# Dependencies
## C++
+ FreeRTOS
+ LWESP
+ json-maker
+ tine-json

# Build
Expects cmake variable to point to config file director where it will include MQTTConfig.h

example:
set(TWIN_THING_PICO_CONFIG_PATH ${CMAKE_CURRENT_LIST_DIR}/src/config)