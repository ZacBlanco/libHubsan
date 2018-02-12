#include "libA7105.h"

libA7105::libA7105()
{
	int _cspin = 0;
}

void libA7105::setupA7105(int cspin)
{
	// Configure SPI parameters for the A7105.
	// SPI_MSB_FIRST - most-significant-bit first.
	// SPI_A7105_CLK_FREQ - The A7105 clock operation frequency (For a raspiberry pi this is the clock / 64)
		// See BCM2835 library documentation for more clock divider constants
	// SPI_MODE0 - rising edge, clock idle low.

	_cspin = cspin;
	SPI_begin();
	SPI_settings(SPI_MSB_FIRST, SPI_A7105_CLK_FREQ, SPI_MODE0);
	SPI_chipSelect(_cspin);
	writeRegister(A7105_00_MODE, 0x00);		  // Issue full reset command to A7105.
	writeRegister(A7105_0B_GIO1_PIN_I, 0x19); // configure 4-wire SPI (GIO1 to MISO)
	byte spimode = 0xFF;
	readRegister(A7105_0B_GIO1_PIN_I, &spimode);
	printf("4-wire in use reg: %x\n", spimode);
}

void libA7105::readRegister(byte address, uint32_t len, byte pdata_r[])
{
	// Read data from the addressed control register - MULTIPLE BYTES
	byte* sr = (byte*)calloc((len+1), sizeof(byte));
	sr[0] = 0x40 | address;
	SPI_transfer(0x40 | address); // READ flag + address.
	SPI_transfern(sr, len+1);
	memcpy(pdata_r, sr+1, len);
	free(sr);

}
void libA7105::readRegister(byte address, byte* pdata_r)
{
	// Read data from the addressed control register - SINGLE BYTE
	byte a[] = { 0x00, 0x00 };
	a[0] = 0x40 | address;
	SPI_transfern(a, 2);
	*pdata_r = a[1];
}

void libA7105::writeRegister(byte address, uint32_t len, byte pdata_w[])
{
	// Write data to the addressed control register - MULTIPLE BYTES
	byte* sr = (byte*)calloc(len+1, sizeof(byte));
	sr[0] = address;
	memcpy(sr+1, pdata_w, len);
	SPI_transfern(sr, len+1);
	free(sr);
}

void libA7105::writeRegister(byte address, byte pdata_w)
{
	// Write data to the addressed control register - SINGLE BYTE
	byte a[] = { address, pdata_w };
	SPI_transfern(a, 2); // Send address and write flag
}

void libA7105::sendStrobe(enum A7105_State strobe)
{
	// Send A7105 state machine STROBE commands.
	SPI_transfer(strobe);
}
