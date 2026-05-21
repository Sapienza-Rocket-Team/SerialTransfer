#include "SerialTransfer.h"
#include "pico/stdlib.h"

#include <cstdio>


/*
 void SerialTransfer::begin(Stream &_port, configST configs)
 Description:
 ------------
  * Advanced initializer for the SerialTransfer Class
 Inputs:
 -------
  * const Stream &_port - Serial port to communicate over
  * const configST configs - Struct that holds config
  values for all possible initialization parameters
 Return:
 -------
  * void
*/
void SerialTransfer::begin(i2c_inst_t* _port, const configST configs)
{
	port = _port;
	packet.begin(configs);
}


/*
 void SerialTransfer::begin(Stream &_port, const bool _debug, Stream &_debugPort)
 Description:
 ------------
  * Simple initializer for the SerialTransfer Class
 Inputs:
 -------
  * const Stream &_port - Serial port to communicate over
  * const bool _debug - Whether or not to print error messages
  * const Stream &_debugPort - Serial port to print error messages
 Return:
 -------
  * void
*/
void SerialTransfer::begin(i2c_inst_t* _port, uint32_t _timeout)
{
	port    = _port;
	timeout = _timeout;
	packet.begin(_timeout);
}

/*
 uint8_t SerialTransfer::sendData(const uint16_t &messageLen, const uint8_t packetID)
 Description:
 ------------
  * Send a specified number of bytes in packetized form
 Inputs:
 -------
  * const uint16_t &messageLen - Number of values in txBuff
  to send as the payload in the next packet
  * const uint8_t packetID - The packet 8-bit identifier
 Return:
 -------
  * uint8_t numBytesIncl - Number of payload bytes included in packet
*/
uint8_t SerialTransfer::sendData(const uint16_t& messageLen, const u32 address, const uint8_t packetID)
{

	uint8_t numBytesIncl = packet.constructPacket(messageLen, packetID);
	i2c_write_blocking(port, address, packet.preamble, sizeof(packet.preamble), false);
	i2c_write_blocking(port, address, packet.txBuff, numBytesIncl, false);
	i2c_write_blocking(port, address, packet.postamble, sizeof(packet.postamble), false);

	return numBytesIncl;
}

int SerialTransfer::recvData(const uint8_t addr, uint8_t length)
{
	return i2c_read_blocking( port, addr, packet.rxBuff, length, false );
}

/*
 uint8_t SerialTransfer::available()
 Description:
 ------------
  * Parses incoming serial data, analyzes packet contents,
  and reports errors/successful packet reception
 Inputs:
 -------
  * void
 Return:
 -------
  * uint8_t bytesRead - Num bytes in RX buffer
*/
/* uint8_t SerialTransfer::available()
{
	bool    valid   = false;
	uint8_t recChar = 0xFF;

	uint8_t src[ 32 ];
	i2c_read_raw_blocking(port, src,

	if ()
	{
		valid = true;

		while (uart_is_readable(port))
		{
			recChar = uart_getc(port);

			bytesRead = packet.parse(recChar, valid);
			status    = packet.status;

			if (status != CONTINUE)
			{
				if (status < 0)
					reset();

				break;
			}
		}
	}
	else
	{
		bytesRead = packet.parse(recChar, valid);
		status    = packet.status;

		if (status < 0)
			reset();
	}

	return bytesRead;
}
*/

/*
 bool SerialTransfer::tick()
 Description:
 ------------
  * Checks to see if any packets have been fully parsed. This
  is basically a wrapper around the method "available()" and
  is used primarily in conjunction with callbacks
 Inputs:
 -------
  * void
 Return:
 -------
  * bool - Whether or not a full packet has been parsed
*/


/*
 uint8_t SerialTransfer::currentPacketID()
 Description:
 ------------
  * Returns the ID of the last parsed packet
 Inputs:
 -------
  * void
 Return:
 -------
  * uint8_t - ID of the last parsed packet
*/
uint8_t SerialTransfer::currentPacketID()
{
	return packet.currentPacketID();
}


/*
 void SerialTransfer::reset()
 Description:
 ------------
  * Clears out the tx, and rx buffers, plus resets
  the "bytes read" variable, finite state machine, etc
 Inputs:
 -------
  * void
 Return:
 -------
  * void
*/
void SerialTransfer::reset()
{
	packet.reset();
	status = packet.status;
}

