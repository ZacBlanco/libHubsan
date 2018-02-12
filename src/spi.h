# ifndef __ZBSPI
# define __ZBSPI

#include <bcm2835.h>
#include <stdio.h>

#define SPI_MODE0 BCM2835_SPI_MODE0
#define SPI_A7105_CLK_FREQ BCM2835_SPI_CLOCK_DIVIDER_64
#define SPI_MSB_FIRST BCM2835_SPI_BIT_ORDER_MSBFIRST
#define SPI_LSB_FIRST BCM2835_SPI_BIT_ORDER_LSBFIRST
#define SPI_CHIP0 BCM2835_SPI_CS0
#define SPI_CHIP1 BCM2835_SPI_CS1

typedef char byte;

/**
  Initialize the BCM and containing SPI library.
  Returns:
    1: Successful initialization
    0: Error on intialization
*/
int SPI_begin();

/**
  Closes the SPI library and resets the GPIO pins.
*/
void SPI_end();


/**
  Sets the SPI settings
  Arguments:
    bit_order: The bit order of the transfer
    clk_divider: The clock divider (to get the correct clock rate on SCK)
    data_mode: The 
*/
void SPI_settings(uint8_t bit_order,
                  uint16_t clk_divider,
                  uint8_t data_mode);

/**
  Sets the SPI pin to be asserted LOW on data transfers.
  
  If you have multiple devices connected to your MOSI and MISO lines
  use this function to 
  
*/
void SPI_chipSelect(uint8_t cs);

uint8_t SPI_transfer(byte data);

void SPI_transfern(byte* buf, uint32_t len);

#endif
