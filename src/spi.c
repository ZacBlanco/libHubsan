#include "spi.h"

int SPI_begin()
{
  if (!bcm2835_init())
  {
    printf("Could not initialize BCM library. Are you running as root?\n");
    return 0;
  }
  
  if (!bcm2835_spi_begin())
  {
    printf("Could not initialize BCM library. Are you running as root?\n");
    return 0;
  }
  return 1;
}

void SPI_end()
{
  bcm2835_spi_end();
  bcm2835_close();
}

void SPI_settings(uint8_t bit_order,
                  uint16_t clk_divider,
                  uint8_t data_mode)
{
  bcm2835_spi_setBitOrder(bit_order);
  bcm2835_spi_setClockDivider(clk_divider);
  bcm2835_spi_setDataMode(data_mode);
}

void SPI_chipSelect(uint8_t cs)
{
  bcm2835_spi_chipSelect(cs);
}

uint8_t SPI_transfer(byte data)
{
  return bcm2835_spi_transfer(data);
}

void SPI_transfern(byte* buf, uint32_t len)
{
  bcm2835_spi_transfern(buf, len);
  return;
}



