cmake_minimum_required( VERSION 3.22 )

# setup pico sdk
list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/_cmake/module" )
include( "_cmake/pico_vsc.cmake" )
include( "_cmake/pico_sdk.cmake" )

project( SerialTransfer CXX C ASM )

# initialize pico-sdk
pico_sdk_init()

# base options
set( SERIAL_TRANSFER_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include" )

# load targets
include( "src/library.cmake" )

option(build_examples "" OFF)

if(${build_examples})
    include( "examples/examples.cmake" )
endif()
