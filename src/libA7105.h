/*
	libA7105.h - Library for interfacing with the AMIC A7105-based XL7105 Transceiver.
	Created by James E. Hung, April 12, 2014. www.jimhung.com
*/
#ifndef libA7105_H
#define libA7105_H

#include <stdlib.h>
#include <string.h>
#include "spi.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

static const byte A7105_00_MODE           = 0x00;
static const byte A7105_01_MODE_CONTROL   = 0x01;
static const byte A7105_02_CALIB_CONT     = 0x02;
static const byte A7105_03_FIFO_I         = 0x03;
static const byte A7105_04_FIFO_II        = 0x04;
static const byte A7105_05_FIFO_DATA      = 0x05;
static const byte A7105_06_ID_DATA        = 0x06;
static const byte A7105_07_RC_OSC_I       = 0x07;
static const byte A7105_08_RC_OSC_II      = 0x08;
static const byte A7105_09_RC_OSC_III     = 0x09;
static const byte A7105_0A_CKO_PIN        = 0x0A;
static const byte A7105_0B_GIO1_PIN_I     = 0x0B;
static const byte A7105_0C_GIO2_PIN_II    = 0x0C;
static const byte A7105_0D_CLOCK          = 0x0D;
static const byte A7105_0E_DATA_RATE      = 0x0E;
static const byte A7105_0F_PLL_I          = 0x0F;
static const byte A7105_10_PLL_II         = 0x10;
static const byte A7105_11_PLL_III        = 0x11;
static const byte A7105_12_PLL_IV         = 0x12;
static const byte A7105_13_PLL_V          = 0x13;
static const byte A7105_14_TX_I           = 0x14;
static const byte A7105_15_TX_II          = 0x15;
static const byte A7105_16_DELAY_I        = 0x16;
static const byte A7105_17_DELAY_II       = 0x17;
static const byte A7105_18_RX             = 0x18;
static const byte A7105_19_RX_GAIN_I      = 0x19;
static const byte A7105_1A_RX_GAIN_II     = 0x1A;
static const byte A7105_1B_RX_GAIN_III    = 0x1B;
static const byte A7105_1C_RX_GAIN_IV     = 0x1C;
static const byte A7105_1D_RSSI_THRESH    = 0x1D;
static const byte A7105_1E_ADC            = 0x1E;
static const byte A7105_1F_CODE_I         = 0x1F;
static const byte A7105_20_CODE_II        = 0x20;
static const byte A7105_21_CODE_III       = 0x21;
static const byte A7105_22_IF_CALIB_I     = 0x22;
static const byte A7105_23_IF_CALIB_II    = 0x23;
static const byte A7105_24_VCO_CUR_CALIB  = 0x24;
static const byte A7105_25_VCO_SB_CAL_I   = 0x25;
static const byte A7105_26_VCO_SB_CAL_II  = 0x26;
static const byte A7105_27_BATT_DETECT    = 0x27;
static const byte A7105_28_TX_TEST        = 0x28;
static const byte A7105_29_RX_DEM_TEST_I  = 0x29;
static const byte A7105_2A_RX_DEM_TEST_II = 0x2A;
static const byte A7105_2B_CHRG_PUMP_CUR  = 0x2B;
static const byte A7105_2C_XTAL_TEST      = 0x2C;
static const byte A7105_2D_PLL_TEST       = 0x2D;
static const byte A7105_2E_VCO_TEST_I     = 0x2E;
static const byte A7105_2F_VCO_TEST_II    = 0x2F;
static const byte A7105_30_IFAT           = 0x30;
static const byte A7105_31_RSCALE         = 0x31;
static const byte A7105_32_FILTER_TEST    = 0x32;

static const byte A7105_STATE_SLEEP     = 0x80;
static const byte A7105_STATE_IDLE      = 0x90;
static const byte A7105_STATE_STANDBY   = 0xA0;
static const byte A7105_STATE_PLL       = 0xB0;
static const byte A7105_STATE_RX        = 0xC0;
static const byte A7105_STATE_TX        = 0xD0;
static const byte A7105_STATE_RST_WRPTR = 0xE0;
static const byte A7105_STATE_RST_RDPTR = 0xF0;


// static uint8_t A7105_CSPIN = -1;

void a7105_setup(int cspin); // Setup SPI characteristics. 4-wire configuration.

void a7105_readRegister2(byte address, uint32_t len, byte* pdata_r); // Read control reg - multiple bytes.

void a7105_readRegister1(byte address, byte* pdata_r); // Read control reg - single byte.

void a7105_writeRegister2(byte address, uint32_t len, byte* pdata_w); // Write control reg - multiple bytes.

void a7105_writeRegister1(byte address, byte pdata_w); // Write control reg - single byte.


// Send STROBE signal.
// One of the A7105_STATE_
void a7105_sendStrobe(int A7105_State);

#endif
