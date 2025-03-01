# uart_rx_with_callbacks.cmake

set( UART_RX_WITH_CALLBACKS_DIR ${CMAKE_CURRENT_LIST_DIR} )

add_executable( uart_rx_with_callbacks
        "${UART_RX_WITH_CALLBACKS_DIR}/uart_rx_with_callbacks.cpp"
)

# create pico-specific files etc.
pico_add_extra_outputs( uart_rx_with_callbacks )
# enable serial output via usb
pico_enable_stdio_usb( uart_rx_with_callbacks 1 )

# pull in common dependencies
target_link_libraries( uart_rx_with_callbacks
        PUBLIC
        SerialTransfer
)
