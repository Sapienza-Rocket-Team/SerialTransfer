# uart_rx_file.cmake

set( UART_RX_FILE_DIR ${CMAKE_CURRENT_LIST_DIR} )

add_executable( uart_rx_file
        "${UART_RX_FILE_DIR}/uart_rx_file.cpp"
)

# create pico-specific files etc.
pico_add_extra_outputs( uart_rx_file )
# enable serial output via usb
pico_enable_stdio_usb( uart_rx_file 1 )

# pull in common dependencies
target_link_libraries( uart_rx_file
        PUBLIC
        SerialTransfer
)
