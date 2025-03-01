# uart_tx_datum.cmake

set( UART_TX_DATUM_DIR ${CMAKE_CURRENT_LIST_DIR} )

add_executable( uart_tx_datum
        "${UART_TX_DATUM_DIR}/uart_tx_datum.cpp"
)

# create pico-specific files etc.
pico_add_extra_outputs( uart_tx_datum )
# enable serial output via usb
pico_enable_stdio_usb( uart_tx_datum 1 )

# pull in common dependencies
target_link_libraries( uart_tx_datum
        PUBLIC
        SerialTransfer
)
