# library.cmake

set( SERIAL_TRANSFER_DIR ${CMAKE_CURRENT_LIST_DIR} )

add_library( SerialTransfer STATIC
    "${SERIAL_TRANSFER_DIR}/Packet.cpp"
    "${SERIAL_TRANSFER_DIR}/Packet.h"
    "${SERIAL_TRANSFER_DIR}/PacketCRC.h"
    "${SERIAL_TRANSFER_DIR}/SerialTransfer.cpp"
    "${SERIAL_TRANSFER_DIR}/SerialTransfer.h"
)

add_library( SerialTransfer::SerialTransfer ALIAS SerialTransfer )

# pull in common dependencies
target_link_libraries( SerialTransfer
    PUBLIC
        pico_stdlib
        hardware_spi
)
