#include "Arduino.h"
#include "libA7105.h"
#include <SPI.h>

libA7105::libA7105()
{
	int _cspin = 0;
}

void libA7105::setupA7105(int cspin)
{
	// Configure SPI parameters for the Due and A7105.
	// SPI_MODE0 - rising edge, clock idle low.
	// MSBFIRST - most-significant-bit first.

	_cspin = cspin;
	pinMode(_cspin, OUTPUT);
	Serial.print("CSPIN: ");
	Serial.println(_cspin);
	digitalWrite(_cspin, HIGH);
	SPISettings spis = SPISettings(A7105_FREQ_MAX, MSBFIRST, SPI_MODE0);
	SPI.beginTransaction(spis);
	SPI.begin(); // Starts out SPI session
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	writeRegister(A7105_00_MODE, 0x00);		  // Issue full reset command to A7105.
	writeRegister(A7105_0B_GIO1_PIN_I, 0x19); // configure 4-wire SPI (GIO1 to MISO)
	byte spimode = 0xFF;
	readRegister(A7105_0B_GIO1_PIN_I, spimode);
	Serial.print("4-wire in use reg: ");
	Serial.println(spimode, HEX);
}

void libA7105::readRegister(byte address, int len, byte pdata_r[])
{
	// Read data from the addressed control register - MULTIPLE BYTES
	digitalWrite(_cspin, LOW);
	SPI.transfer(0x40 | address); // READ flag + address.
	for (int i = 0; i < len; i++)
	{
		pdata_r[i] = SPI.transfer(0x00); 
	}
	digitalWrite(_cspin, HIGH); // release Chip-Select on last byte.
}

void libA7105::readRegister(byte address, byte &pdata_r)
{
	// Read data from the addressed control register - SINGLE BYTE
	digitalWrite(_cspin, LOW);
	SPI.transfer(0x40 | address); // READ flag + address.
	pdata_r = SPI.transfer(0x00);
	digitalWrite(_cspin, HIGH);
}

void libA7105::writeRegister(byte address, int len, byte pdata_w[])
{
	// Write data to the addressed control register - MULTIPLE BYTES
	digitalWrite(_cspin, LOW);
	SPI.transfer(address); // Send address and Write flag.
	for (int i = 0; i < (len); i++)
	{
		SPI.transfer(pdata_w[i]);
	}
	digitalWrite(_cspin, HIGH);
}

void libA7105::writeRegister(byte address, byte pdata_w)
{
	// Write data to the addressed control register - SINGLE BYTE
	digitalWrite(_cspin, LOW);
	SPI.transfer(address); // Send address and Write flag.
	SPI.transfer(pdata_w); // release Chip-Select on last byte.
	digitalWrite(_cspin, HIGH);
}

void libA7105::sendStrobe(enum A7105_State strobe)
{
	// Send A7105 state machine STROBE commands.
	digitalWrite(_cspin, LOW);
	SPI.transfer(strobe);
	digitalWrite(_cspin, HIGH);
}
