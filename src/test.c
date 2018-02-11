#include <stdio.h>
#include "spi.h"
#include "libA7105.h"
typedef uint8_t byte;

libA7105 chip;

int main(int argc, char** argv)
{
  if(!SPI_begin())
  {
    return 1;
  }
 // SPI_settings();
  printf("SPI test program\n");
  SPI_settings(SPI_MSB_FIRST, SPI_A7105_CLK_FREQ, SPI_MODE0);
  //byte a = 0xb5;
  //byte b = SPI_transfer(a);
  //printf("Received %x on transfer\n", b);
  //chip.setupA7105(SPI_CHIP0);
  //byte a = SPI_transfer(0x40 | 0x0);
  char a[] = { 0x00, 0x00};
  SPI_transfern(a, 2);
  printf("Received 0x%x 0x%x\n", a[0], a[1]);
  a[0] = 0x0B;
  a[1] = 0x19;
  SPI_transfern(a, 2);
  printf("Received 0x%x 0x%x\n", a[0], a[1]);
  a[0] = 0x4B;
  a[1] = 0xFF;
  SPI_transfern(a, 2);
  printf("Received 0x%x 0x%x\n", a[0], a[1]);
  SPI_end();
}