#include "libHubsan.h"

const byte _channels[12] = {0x14, 0x1E, 0x28, 0x32, 0x3C, 0x46, 0x50, 0x5A, 0x64, 0x6E, 0x78, 0x82};

void libHubsan_init(int cspin)
{
	// Initialize A7015 settings for the Hubsan quadcopter.
	a7105_setup(cspin); // Configure A7105 for SPI comms.

	// Set ID Code Register (x06) to "55 20 10 41".
	//printf("here\n");
	byte idcode[4] = {0x55, 0x20, 0x10, 0x41};
	a7105_writeRegister2(A7105_06_ID_DATA, 4, idcode);
	// Set Mode Control Register (x01) Auto RSSI measurement, Auto IF Offset, FIFO mode enabled.
	a7105_writeRegister1(A7105_01_MODE_CONTROL, 0x63);
	// Set Calibration Control Reg (x02) - Reset.
	a7105_writeRegister1(A7105_02_CALIB_CONT, 0x00);
	// Set FIFO Register 1 (x03) - Set FIFO length to 16 bytes
	a7105_writeRegister1(A7105_03_FIFO_I, 0x0F);
	// Set FIFO Register 2 (x04) - 16 Byte TX/RX.
	a7105_writeRegister1(A7105_04_FIFO_II, 0xC0);
	// Set RC OSC Reg 1 (x07) - Reset.
	a7105_writeRegister1(A7105_07_RC_OSC_I, 0x00);
	// Set RC OSC Reg 2 (x08) - Reset.
	a7105_writeRegister1(A7105_08_RC_OSC_II, 0x00);
	// Set RC OSC Reg 3 (x09) - RC-oscillator Enable.
	a7105_writeRegister1(A7105_09_RC_OSC_III, 0x04);
	// Set CKO Pin Control Register (x0A) - Disable CLK out, TX clock, RX Recovery CLK, Non-Inverted CLK, Hi-Z CLK Out, Non-Inverted SPI Pin CLK.
	a7105_writeRegister1(A7105_0A_CKO_PIN, 0x00);
	// OMITTED: Set GIO1 Pin Control Register (x0B) - Reset.
	// Set GIO2 Pin Control Register (x0C) - GIO2 Pin Enable.
	a7105_writeRegister1(A7105_0C_GIO2_PIN_II, 0x01);
	// Set Clock Register (x0D) - Use Crystal Oscillator, CLK divider = /2.
	a7105_writeRegister1(A7105_0D_CLOCK, 0x05);
	// Set Data Rate Register (x0E) - Set data rate to 25kbps.
	a7105_writeRegister1(A7105_0E_DATA_RATE, 0x04);
	// Set PLL Register 1 (x0F) - Set Channel Offset to 80.
	a7105_writeRegister1(A7105_0F_PLL_I, 0x50);
	// Set PLL Register 2 (x10) - Reset.
	a7105_writeRegister1(A7105_10_PLL_II, 0x9E);
	// Set PLL Register 3 (x11) - Reset.
	a7105_writeRegister1(A7105_11_PLL_III, 0x4B);
	// Set PLL Register 4 (x12) - Reset.
	a7105_writeRegister1(A7105_12_PLL_IV, 0x00);
	// Set PLL Register 5 (x13) - Autofrequency Compensation.
	a7105_writeRegister1(A7105_13_PLL_V, 0x00);
	// Set TX Register 1 (x14) - Reset.
	a7105_writeRegister1(A7105_14_TX_I, 0x16);
	// Set TX Register 2 (x15) - Frequency Deviation: 186KHz
	a7105_writeRegister1(A7105_15_TX_II, 0x2B);
	// Set Delay Register 1 (x16) - Reset.
	a7105_writeRegister1(A7105_16_DELAY_I, 0x12);
	// Set Delay Register 2 (x17) - 200us settling delay, 10us AGC delay settling, 10us RSSI measurement delay.
	a7105_writeRegister1(A7105_17_DELAY_II, 0x00);
	// Set RX Register (x18) - BPF bandwidth = 500 KHz.
	a7105_writeRegister1(A7105_18_RX, 0x62);
	// Set RX Gain Register 1 (x19) - Manual VGA, Mixer Gain: 24dB, LNA gain: 24dB.
	a7105_writeRegister1(A7105_19_RX_GAIN_I, 0x80);
	// Set RX Gain Register 2 (x1A) - Internal Use?
	a7105_writeRegister1(A7105_1A_RX_GAIN_II, 0x80);
	// Set RX Gain Register 3 (x1B) - Internal Use?
	a7105_writeRegister1(A7105_1B_RX_GAIN_III, 0x00);
	// Set RX Gain Register 4 (x1C) - Reserved.
	a7105_writeRegister1(A7105_1C_RX_GAIN_IV, 0x0A);
	// Set RSSI Threshold Register (x1D) to x32.
	a7105_writeRegister1(A7105_1D_RSSI_THRESH, 0x32);
	// Set ADC Control Register (x1E) - RSSI Margin: 20, RSSI Measurement continue, FSARS: 4 MHZ, XADS = Convert RSS, RSSI measurement selected, RSSI continuous mode.
	a7105_writeRegister1(A7105_1E_ADC, 0xC3);
	// Set Code Register 1 (x1F) - Reset.
	a7105_writeRegister1(A7105_1F_CODE_I, 0x07);
	// Set Code Register 2 (x20) - Demodulator avg mode, 2 bit ID error code tolerance, 16bit  preamble detect.
	a7105_writeRegister1(A7105_20_CODE_II, 0x17);
	// Set Code Register 3 (x21) - Encryption Key (XOR…) - All zeroes (Data Whitening not enabled in register x1F.
	a7105_writeRegister1(A7105_21_CODE_III, 0x00);
	// Set IF Calibration Register (x22) - Autocalibrate.
	a7105_writeRegister1(A7105_22_IF_CALIB_I, 0x00);
	// Set VCO Current Calibration Reg (x24) - Autocalibrate.
	a7105_writeRegister1(A7105_24_VCO_CUR_CALIB, 0x00);
	// Set VCO Single band Calibration Reg (x25) - Autocalibrate.
	a7105_writeRegister1(A7105_25_VCO_SB_CAL_I, 0x00);
	// Set VCO Single band Calibration Reg 2 (x26) - Upper threshold: -1.3V, Lower threshold: 0.4V
	a7105_writeRegister1(A7105_26_VCO_SB_CAL_II, 0x3B);
	// Set Battery Detect Register (x27) - 2V battery detect threshold.
	a7105_writeRegister1(A7105_27_BATT_DETECT, 0x00);
	// Set TX Test Register (x28) - Reset.
	a7105_writeRegister1(A7105_28_TX_TEST, 0x17);
	// Set RX DEM test Reg (x29) - Internal Use?
	a7105_writeRegister1(A7105_29_RX_DEM_TEST_I, 0x47);
	// Set RX DEM test Reg 2 (x2A) - Reset.
	a7105_writeRegister1(A7105_2A_RX_DEM_TEST_II, 0x80);
	// Set Charge Pump Current Reg (x2B) - 2.0mA.
	a7105_writeRegister1(A7105_2B_CHRG_PUMP_CUR, 0x03);
	// Set Crystal Test Reg (x2C) - Internal Use?
	a7105_writeRegister1(A7105_2C_XTAL_TEST, 0x01);
	// Set PLL test Register (x2D) - Internal Use?
	a7105_writeRegister1(A7105_2D_PLL_TEST, 0x45);
	// Set VCO test Reg (x2E) - Internal Use?
	a7105_writeRegister1(A7105_2E_VCO_TEST_I, 0x18);
	// Set VCO test reg 2 (x2F) - Internal Use?
	a7105_writeRegister1(A7105_2F_VCO_TEST_II, 0x00);
	// Set IFAT reg (x30) - Internal Use?
	a7105_writeRegister1(A7105_30_IFAT, 0x01);
	// Set RSCALE reg (x31) - Reset.
	a7105_writeRegister1(A7105_31_RSCALE, 0x0F);

	// CALIBRATION TESTS
	byte test_result; // var to hold the test results for each calibration test in turn.
	int timeout;	  // var to hold timeout watchdog counter.
	int i, j; // loop iterator

	// IF Filter Bank Calibration START.
	printf("Performing IF Filter Bank Calibration Test.\n");
	timeout = 0;
	a7105_sendStrobe(A7105_STATE_STANDBY);				// Strobe - STANDBY.
	a7105_writeRegister1(A7105_02_CALIB_CONT, 0x01); // Set Calibration Control Reg (x02) - IF Filter Bank calibration enable.
	while (1)
	{
		a7105_readRegister1(A7105_02_CALIB_CONT, &test_result);
		if (test_result == 0x00)
		{
			break;
		}
		if (timeout > 10)
		{ // Allow 10 iterations before signalling a failure.
			printf("ERROR: IF Filter Bank Calibration Test FAILED - (timeout).\n");
		}
		timeout++;
		usleep(20);
	}
	a7105_readRegister1(A7105_22_IF_CALIB_I, &test_result);
	if (CHECK_BIT(test_result, 4))
	{
		printf("ERROR: IF Filter Bank Calibration Test FAILED - FBCF Flag: %x\n", test_result);
	}
	else
	{
		printf(" - Passed.\n");
	}
	a7105_writeRegister1(A7105_22_IF_CALIB_I, 0x13);  //Set IF Calibration Register - Configure relative control calibration.
	a7105_writeRegister1(A7105_23_IF_CALIB_II, 0x3B); // Set IF Calibration Register 2 - as above.

	// VCO Bank Calibration - TEST 1: START
	printf("Performing VCO Bank Calibration - Test 1\n");
	timeout = 0;
	a7105_writeRegister1(A7105_0F_PLL_I, 0x00);		// Set PLL Register 1 - Reset.
	a7105_sendStrobe(A7105_STATE_PLL);					// Strobe - PLL Mode.
	a7105_writeRegister1(A7105_02_CALIB_CONT, 0x02); // Set Calibration Control Reg - VCO Bank Calibration enable.
	while (1)
	{
		a7105_readRegister1(A7105_02_CALIB_CONT, &test_result);
		if (test_result == 0x00)
		{
			break;
		}
		if (timeout > 10)
		{ // Allow 10 iterations before signalling a failure.
			printf("ERROR: VCO Bank Calibration Test FAILED - (timeout).\n");
		}
  		timeout++;
		delayMicroseconds(20);
	}
	a7105_readRegister1(A7105_25_VCO_SB_CAL_I, &test_result);
	if (CHECK_BIT(test_result, 3))
	{
		printf("ERROR: VCO Bank Calibration Test FAILED - VBCF Flag: %x\n", test_result);
	}
	else
	{
		printf(" - Passed.\n");
	}
	a7105_writeRegister1(A7105_0F_PLL_I, 0x78); // Set PLL Register 1 - Select Channel Offset.

	// VCO Bank Calibration - TEST 2: START
	printf("Performing VCO Bank Calibration - Test 2\n");
	timeout = 0;
	a7105_sendStrobe(A7105_STATE_PLL);					// Strobe - PLL Mode.
	a7105_writeRegister1(A7105_02_CALIB_CONT, 0x02); // Set Calibration Control Reg - VCO Bank Calibration enable.
	while (1)
	{
		a7105_readRegister1(A7105_02_CALIB_CONT, &test_result);
		if (test_result == 0x00)
		{
			break;
		}
		if (timeout > 10)
		{ // Allow 10 iterations before signalling a failure.
			printf("ERROR: VCO Bank Calibration Test FAILED - (timeout).\n");
		}
		timeout++;
		delayMicroseconds(20);
	}
	a7105_readRegister1(A7105_25_VCO_SB_CAL_I, &test_result);
	if (CHECK_BIT(test_result, 3))
	{
		printf("ERROR: VCO Bank Calibration Test FAILED - VBCF Flag: %x\n", test_result);
	}
	else
	{
		printf(" - Passed.\n");
	}
	a7105_writeRegister1(A7105_25_VCO_SB_CAL_I, 0x0B); // Set VCO Single band Calibration Register 1 - Manual Calibration settings.

	a7105_sendStrobe(A7105_STATE_STANDBY);

	a7105_readRegister2(A7105_06_ID_DATA, 4, idcode);
	printf("ID CODE: 0x%x 0x%x 0x%x 0x%x\n", idcode[0], idcode[1], idcode[2], idcode[3]);

	a7105_writeRegister1(A7105_0F_PLL_I, 0xA0); // Set PLL Register 1 - Select Channel Offset.
	a7105_sendStrobe(A7105_STATE_PLL);
	a7105_sendStrobe(A7105_STATE_RX);

	// Setup RSSI measurement.
	a7105_writeRegister1(A7105_1E_ADC, 0xC3); // Set ADC Control Register (x1E) - RSSI Margin: 20, RSSI Measurement continue, FSARS: 4 MHZ, XADS = Convert RSS, RSSI measurement selected, RSSI continuous mode.

	// Cycle through the 12 channels and identify the best one to use.
	printf("Scanning Channel RSSI values: \n");
	long chan_rssi[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (i = 0; i < 12; i++)
	{
		a7105_writeRegister1(A7105_0F_PLL_I, _channels[i]); // Set PLL Register 1 - Select Channel Offset.
		a7105_sendStrobe(A7105_STATE_PLL);
		a7105_sendStrobe(A7105_STATE_RX);
		for (j = 0; j < 15; j++)
		{
			a7105_readRegister1(A7105_1D_RSSI_THRESH, &test_result);
			chan_rssi[i] = (chan_rssi[i] + test_result);
		}
	}
	int temp_rssi = 0;
	for (i = 0; i < 12; i++)
	{
		if (chan_rssi[i] > temp_rssi)
		{
			temp_rssi = chan_rssi[i];
			_channel = _channels[i];
		}
	}
	printf(" - Selected Channel: 0x%x\n", _channel);
	a7105_writeRegister1(A7105_28_TX_TEST, 0x1F);   // Set TX test Register - TX output: -4.8dBm, current: 14.9mA.
	a7105_writeRegister1(A7105_19_RX_GAIN_I, 0x9B); // Set RX Gain register - Manual, Mixer gain: 6dB, LNA gain: 6dB
	byte data = 0x00;
	a7105_readRegister1(A7105_28_TX_TEST, &data);
	printf("tx gain reg: 0x%x\n", data);
	a7105_writeRegister1(A7105_0F_PLL_I, _channel); // Set PLL Register 1 - Select Channel Offset to channel with the HIGHEST average RSSI from the scanning
	a7105_sendStrobe(A7105_STATE_PLL);
	a7105_sendStrobe(A7105_STATE_STANDBY);
}

void libHubsan_printPacket(const char *msg, byte *packet)
{
	int i;
	//printf("%s: ", msg);
	for (i = 0; i < 16; i++)
	{
	//	printf("0x%x ", packet[i]);
	}
	//printf("\n");
}

void libHubsan_bind()
{
	int i, j; //loop iterator
	printf("Sending beacon packets...\n");
	byte status_byte = 0x00; // variable to hold W/R register data.

	// Generate 4 byte random session id.
	srand(time(NULL));
	for (i = 0; i < 4; i++)
	{
		_sessionid[i] = rand() % 255;
	}

	for (i = 0; i < 16; i++)
	{ // Initialize packet array.
		_txpacket[i] = 0x00;
	}
	_txpacket[0] = 0x01;	 // Bind level = 01 (Unbound - BEACON lvl 1 Packet)
	_txpacket[1] = _channel; // Selected Channel
	for (i = 0; i < 4; i++)
	{
		_txpacket[i + 2] = _sessionid[i];
	}
	libHubsan_getChecksum(_txpacket);

	// Transmit ANNOUNCE Packet until a response is heard.
	printf("Announce Tx\n");
	while (1)
	{
		libHubsan_txPacket(_txpacket);
		libHubsan_printPacket("Announce packet", _txpacket);
		a7105_sendStrobe(A7105_STATE_RX); // Switch to RX mode.
		int response = 0;
		for (i = 0; i < 15; i++)
		{ // Listen to see if there was a response.
			a7105_readRegister1(A7105_00_MODE, &status_byte);
			if (CHECK_BIT(status_byte, 0) == 0)
			{
				response = 1;
				printf("Got response to ANNOUNCE\n");
				break;
			}
			usleep(1000); // 1ms
		}
		if (response)
		{
			break;
		}
		a7105_sendStrobe(A7105_STATE_STANDBY);
	}
	libHubsan_rxPacket(_rxpacket);
	libHubsan_printPacket("Announce Rx", _rxpacket);

	// Escalate handshake.
	_txpacket[0] = 0x03; // Bind Level = 01 (Unbound - BEACON lvl 3 Packet)
	printf("Escalating bind to Level 01, BEACON lvl 3\n");
	libHubsan_getChecksum(_txpacket);
	while (1)
	{
		libHubsan_txPacket(_txpacket);
		libHubsan_printPacket("Escalation 1 Tx", _txpacket);
		a7105_sendStrobe(A7105_STATE_RX); // Switch to RX mode.
		int response = 0;
		for (i = 0; i < 15; i++)
		{ // Listen to see if there was a response.
			a7105_readRegister1(A7105_00_MODE, &status_byte);
			if (CHECK_BIT(status_byte, 0) == 0)
			{
				response = 1;
				printf("Got Response to BEACON lvl 3 packet\n");
				break;
			}
			usleep(1000); // 1000 microseconds (1ms)
		}
		if (response)
		{
			break;
		}
		a7105_sendStrobe(A7105_STATE_STANDBY);
	}
	libHubsan_rxPacket(_rxpacket);
	libHubsan_printPacket("Escalation 1 Rx", _rxpacket);

	// Set IDCode to the session value.
	a7105_writeRegister2(A7105_06_ID_DATA, 4, _sessionid);

	// Commence confirmation handshake.
	_txpacket[0] = 0x01; // Bind Level = 01 (Mid-Bind - Confirmation of IDCODE change packet)
	printf("Escalating to MidBind\n");
	libHubsan_getChecksum(_txpacket);
	while (1)
	{
		libHubsan_txPacket(_txpacket);
		libHubsan_printPacket("MidBind Tx", _txpacket);
		a7105_sendStrobe(A7105_STATE_RX); // Switch to RX mode.
		int response = 0;
		for (i = 0; i < 15; i++)
		{ // Listen to see if there was a response.
			a7105_readRegister1(A7105_00_MODE, &status_byte);
			if (CHECK_BIT(status_byte, 0) == 0)
			{
				response = 1;
				break;
			}
			usleep(1000); // 1ms
		}
		if (response)
		{
			break;
		}
		a7105_sendStrobe(A7105_STATE_STANDBY);
	}
	libHubsan_rxPacket(_rxpacket);
	libHubsan_printPacket("MidBind Rx", _rxpacket);

	// Commence full handshake escalation.
	printf("commencing full handshake\n");
	_txpacket[0] = 0x09;
	for (i = 0; i < 10; i++)
	{
		printf("before _txpacket\n");
		_txpacket[2] = (byte)i;
		printf("after _txpacket\n");		
		libHubsan_getChecksum(_txpacket);
		while (1)
		{
			printf("inside while(1)\n");
			libHubsan_txPacket(_txpacket);
			libHubsan_printPacket("Full Handshake Tx", _txpacket);
			a7105_sendStrobe(A7105_STATE_RX); // Switch to RX mode.
			int response = 0;
			for (j = 0; j < 15; j++)
			{ // Listen to see if there was a response.
				a7105_readRegister1(A7105_00_MODE, &status_byte);
				if (CHECK_BIT(status_byte, 0) == 0)
				{
					response = 1;
					break;
				}
				usleep(1000); // 1000 microseconds
			}
			if (response)
			{
				break;
			}
			a7105_sendStrobe(A7105_STATE_STANDBY);
		}
		libHubsan_rxPacket(_rxpacket);
		libHubsan_printPacket("Full Handshake Rx", _rxpacket);
	}
	a7105_writeRegister1(A7105_1F_CODE_I, 0x0F); // Enable FEC.
	a7105_sendStrobe(A7105_STATE_STANDBY);
	printf("Binding finished\n");
}

void libHubsan_txPacket(byte* ppacket)
{
	// Transmit packet and wait until it has completed sending before returning.
	int i;
	printf("TX Packet: ");
	for (i = 0; i < 16; i++)
	{
		printf("\\x%x", ppacket[i]);
	}
	printf("\n");
	byte status_byte;
	a7105_sendStrobe(A7105_STATE_RST_WRPTR); // Reset FIFO Write Pointer.
	a7105_writeRegister2(A7105_05_FIFO_DATA, 16, ppacket);
	a7105_sendStrobe(A7105_STATE_TX); // Transmit packet.
	while (1)
	{ // Check to see if the transmission has completed.
		a7105_readRegister1(A7105_00_MODE, &status_byte);
		if (CHECK_BIT(status_byte, 0) == 0)
		{
			break;
		}
	}
}

void libHubsan_rxPacket(byte* ppacket)
{
	// Read received packet from FIFO buffer.
	a7105_sendStrobe(A7105_STATE_RST_RDPTR); // Reset the RX pointer.
	a7105_readRegister2(A7105_05_FIFO_DATA, 16, ppacket); // Read received packet.
}

void libHubsan_getChecksum(byte* ppacket)
{
	// Calculate checksum value. 256-(Sum of packet bytes 0-15, mod 256).

	int sum = 0;
	int i;
	for (i = 0; i < 15; i++)
	{
		sum = sum + (int)ppacket[i];
	}
	printf("Checksum is %x\n", (byte) (256 - (sum % 256)));
	ppacket[15] = (byte) (256 - (sum % 256));
	for (i = 0; i < 16; i++)
	{
		printf("\\x%x", ppacket[i]);
	}
	printf("\n");
}
