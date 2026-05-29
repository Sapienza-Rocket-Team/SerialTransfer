#include "I2CTransfer.h"

#include <cstdio>
#include <cstring>


/*
 void I2CTransfer::begin(i2c_inst_t &_port, configST& configs)
 Description:
 ------------
  * Advanced initializer for the I2CTransfer Class
 Inputs:
 -------
  * const i2c_inst_t &_port - I2C port to communicate over
  * const configST& configs - Struct that holds config
  values for all possible initialization parameters
 Return:
 -------
  * void
*/
void I2CTransfer::begin(i2c_inst_t* _port, const configST& configs)
{
	port = _port;
	packet.begin(configs);
}


/*
 void I2CTransfer::begin(i2c_inst_t &_port, const bool& _debug, Stream &_debugPort)
 Description:
 ------------
  * Simple initializer for the SerialTransfer Class
 Inputs:
 -------
  * const i2c_inst_t &_port - I2C port to communicate over
  * const uint32_t& _timeout - Number of ms to wait before
  declaring packet parsing timeout
 Return:
 -------
  * void
*/
void I2CTransfer::begin(i2c_inst_t* _port, uint32_t _timeout)
{
	port = _port;
	packet.begin(_timeout);
}


/*
 uint8_t I2CTransfer::sendData(const uint16_t &messageLen, const uint8_t &packetID, const uint8_t &targetAddress=0)
 Description:
 ------------
  * Send a specified number of bytes in packetized form
 Inputs:
 -------
  * const uint16_t &messageLen - Number of values in txBuff
  to send as the payload in the next packet
  * const uint8_t &packetID - The packet 8-bit identifier
  * const uint8_t &targetAddress - I2C address to the device the packet
      will be transmitted to
 Return:
 -------
  * uint8_t numBytesIncl - Number of payload bytes included in packet
*/
uint8_t I2CTransfer::sendData(const uint16_t& messageLen, const uint8_t& packetID, const uint8_t targetAddress)
{
	// TODO: check if actually full packet.TxBuffer
	uint8_t numBytesIncl = packet.constructPacket(messageLen, packetID);
	uint8_t temp[PREAMBLE_SIZE + numBytesIncl + PREAMBLE_SIZE];

	memcpy( temp, packet.preamble, sizeof( Packet::preamble ) );
	memcpy( temp + sizeof( Packet::preamble ), packet.txBuff, numBytesIncl );
	memcpy( temp + numBytesIncl + sizeof( Packet::preamble ), packet.postamble, sizeof( Packet::postamble ) );

	int res = i2c_write_blocking( port, targetAddress, temp , sizeof( Packet::preamble ) + numBytesIncl + sizeof( Packet::postamble ), false );
	printf( "target addr %u\n", targetAddress);

	return res;
}


/*
 void I2CTransfer::processData()
 Description:
 ------------
  * Parses incoming serial data automatically when an
  I2C frame is received
 Inputs:
 -------
  * void
 Return:
 -------
  * void
*/
void I2CTransfer::processData( const uint8_t targetAddress )
{
	uint8_t recChar;
	bytesRead = 0;
	int res;

	while ( true )
	{
		res = i2c_read_timeout_us( port, targetAddress, &recChar, 1, false, packet.getTimeout() );
		if ( res == PICO_ERROR_TIMEOUT )
		{
			status = packet.status = STALE_PACKET_ERROR;
		}
		else
		{
			bytesRead = packet.parse(recChar);
			status    = packet.status;
		}

		if (status != CONTINUE)
		{
			if (status < 0)
				reset();

			break;
		}
	}
}


/*
 uint8_t I2CTransfer::currentPacketID()
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
uint8_t I2CTransfer::currentPacketID()
{
	return packet.currentPacketID();
}


/*
 void I2CTransfer::reset()
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
void I2CTransfer::reset()
{
	packet.reset();
	status = packet.status;
}
