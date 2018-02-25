#ifndef __TEST_INCLUDE
#define __TEST_INCLUDE
#include <stdio.h>
#include <unistd.h>
#include "libHubsan.h"
#endif

int main(int argc, char** argv)
{
  printf("%i\n", SPI_CHIP0);
  libHubsan_init(SPI_CHIP0);
  libHubsan_bind();
  byte packet[16] = {0x20, 0x00, 0x05, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x0E, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00 };
  libHubsan_getChecksum(packet);
  usleep(1000000);
  while (1)
  {
    libHubsan_txPacket(packet);
    usleep(1000);
  }
  return 0;
}
