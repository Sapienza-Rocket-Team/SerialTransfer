# uart_rx_datum.cmake

set( UART_RX_DATUM_DIR ${CMAKE_CURRENT_LIST_DIR} )

add_executable( uart_rx_datum
        "${UART_RX_DATUM_DIR}/uart_rx_datum.cpp"
)

# create pico-specific files etc.
pico_add_extra_outputs( uart_rx_datum )
# enable serial output via usb
pico_enable_stdio_usb( uart_rx_datum 1 )

# pull in common dependencies
target_link_libraries( uart_rx_datum
        PUBLIC
        SerialTransfer
)
