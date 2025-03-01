# This is a simplified copy of <PICO_SDK_PATH>/external/pico_sdk_import.cmake

# This can be dropped into an external project to help locate this SDK
# It should be `include`'d prior to `project()`

if ( DEFINED ENV{PICO_SDK_PATH} AND (NOT PICO_SDK_PATH) )
	set( PICO_SDK_PATH "$ENV{PICO_SDK_PATH}" )
	message( NOTICE "Using PICO_SDK_PATH from environment (`${PICO_SDK_PATH}`)" )
endif()

set( PICO_SDK_PATH "${PICO_SDK_PATH}" CACHE PATH "Path to the Raspberry Pi Pico SDK" )
set( PICO_SDK_INIT_CMAKE_FILE "${PICO_SDK_PATH}/pico_sdk_init.cmake" )

if ( NOT IS_ABSOLUTE "${PICO_SDK_PATH}" )
	message( FATAL_ERROR "Path `${PICO_SDK_PATH}` is not absolute" )
elseif ( NOT EXISTS "${PICO_SDK_PATH}" )
	message( FATAL_ERROR "Directory `${PICO_SDK_PATH}` not found" )
elseif ( NOT EXISTS "${PICO_SDK_INIT_CMAKE_FILE}" )
	message( FATAL_ERROR "Directory `${PICO_SDK_PATH}` does not appear to contain the Raspberry Pi Pico SDK" )
endif ()

include( "${PICO_SDK_INIT_CMAKE_FILE}" )
