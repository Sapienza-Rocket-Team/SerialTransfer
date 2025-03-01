# uart_tx_data.cmake

set( UART_TX_DATA_DIR ${CMAKE_CURRENT_LIST_DIR} )

add_executable( uart_tx_data
        "${UART_TX_DATA_DIR}/uart_tx_data.cpp"
)

# create pico-specific files etc.
pico_add_extra_outputs( uart_tx_data )
# enable serial output via usb
pico_enable_stdio_usb( uart_tx_data 1 )

# pull in common dependencies
target_link_libraries( uart_tx_data
        PUBLIC
        SerialTransfer
)
