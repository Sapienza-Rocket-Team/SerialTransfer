# uart_tx_file.cmake

set( UART_TX_FILE_DIR ${CMAKE_CURRENT_LIST_DIR} )

add_executable( uart_tx_file
        "${UART_TX_FILE_DIR}/uart_tx_file.cpp"
)

# create pico-specific files etc.
pico_add_extra_outputs( uart_tx_file )
# enable serial output via usb
pico_enable_stdio_usb( uart_tx_file 1 )

# pull in common dependencies
target_link_libraries( uart_tx_file
        PUBLIC
        SerialTransfer
)
