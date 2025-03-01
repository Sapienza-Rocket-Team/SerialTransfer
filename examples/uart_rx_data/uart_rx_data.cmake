# uart_rx_data.cmake

set( UART_RX_DATA_DIR ${CMAKE_CURRENT_LIST_DIR} )

add_executable( uart_rx_data
    "${UART_RX_DATA_DIR}/uart_rx_data.cpp"
)

# create pico-specific files etc.
pico_add_extra_outputs( uart_rx_data )
# enable serial output via usb
pico_enable_stdio_usb( uart_rx_data 1 )

# pull in common dependencies
target_link_libraries( uart_rx_data
    PUBLIC
        SerialTransfer
)
