# Add library cpp files
set(LWESP_OPTION_OS             "FreeRTOS")
set(LWESP_OPTION_PORT_PATH      ${CMAKE_CURRENT_LIST_DIR}/port/lwesp)
set(LWESP_OPTION_USER_CFG_FILE  ${CMAKE_CURRENT_LIST_DIR}/config/lwesp_opts.h)

set(FREERTOS_PORT_PATH      ${CMAKE_CURRENT_LIST_DIR}/port/FreeRTOS)


add_library(twinThingPicoESP INTERFACE)
target_sources(twinThingPicoESP INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/MQTTAgent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/MQTTInterface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/MQTTRouter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/MQTTRouterPing.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/MQTTPingTask.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/MQTTTopicHelper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/State.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/StateObserver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/StateTemp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/TwinTask.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/MQTTRouterTwin.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/MQTTAgentObserver.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/WifiHelper.cpp
)

# Add include directory
target_include_directories(twinThingPicoESP INTERFACE 
	${CMAKE_CURRENT_LIST_DIR}/src
	${TWIN_THING_PICO_CONFIG_PATH}
)

# Add the standard library to the build
target_link_libraries(twinThingPicoESP INTERFACE pico_stdlib hardware_adc json_maker tiny_json)

