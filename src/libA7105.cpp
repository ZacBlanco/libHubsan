#include "libA7105.h"
#include "spi.h"

libA7105::libA7105()
{
	int _cspin = 0;
}

void libA7105::setupA7105(int cspin)
{
	// Configure SPI parameters for the A7105.
	// SPI_MODE0 - rising edge, clock idle low.
	// SPI_MSB_FIRST - most-significant-bit first.

	_cspin = cspin;
	SPI_begin();
	SPI_settings(SPI_MSB_FIRST, SPI_A7105_CLK_FREQ, SPI_MODE0);
	SPI_chipSelect(_cspin);
	writeRegister(A7105_00_MODE, 0x00);		  // Issue full reset command to A7105.
	writeRegister(A7105_0B_GIO1_PIN_I, 0x19); // configure 4-wire SPI (GIO1 to MISO)
	byte spimode = 0xFF;
	readRegister(A7105_0B_GIO1_PIN_I, spimode);
	printf("4-wire in use reg: %x\n", spimode);
}

void libA7105::readRegister(byte address, int len, byte pdata_r[])
{
	// Read data from the addressed control register - MULTIPLE BYTES
	SPI_transfer(0x40 | address); // READ flag + address.
	for (int i = 0; i < len; i++)
	{
		pdata_r[i] = SPI_transfer(0x00); 
	}
}

void libA7105::readRegister(byte address, byte &pdata_r)
{
	// Read data from the addressed control register - SINGLE BYTE
	SPI_transfer(0x40 | address); // READ flag + address.
	pdata_r = SPI_transfer(0x00);
}

void libA7105::writeRegister(byte address, int len, byte pdata_w[])
{
	// Write data to the addressed control register - MULTIPLE BYTES
	SPI_transfer(address); // Send address and Write flag.
	for (int i = 0; i < (len); i++)
	{
		SPI_transfer(pdata_w[i]);
	}
}

void libA7105::writeRegister(byte address, byte pdata_w)
{
	// Write data to the addressed control register - SINGLE BYTE
	SPI_transfer(address); // Send address and Write flag.
	SPI_transfer(pdata_w); // release Chip-Select on last byte.
}

void libA7105::sendStrobe(enum A7105_State strobe)
{
	// Send A7105 state machine STROBE commands.
	SPI_transfer(strobe);
}
