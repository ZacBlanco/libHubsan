/*
 Hubsan X4 H107L Quadcopter Controller for Arduino Due
  by: Jim Hung (www.jimhung.co.uk) - 2014-04-11

 - Serial baud: 115200
 - A7105 Transceiver SPI Chip Select pin: 45
*/
#include <SPI.h>
#include "libA7105.h"
#include "libHubsan.h"

int rev = 1; // Revision
byte controlbuffer[4] = {byte(0),byte(128),byte(128),byte(128)}; // Array to contain flight axis control values.
byte smoothbuffer[4] = {byte(0),byte(128),byte(128),byte(128)};
byte controlpacket[16]; // Array of control packet bytes.
byte inctype;
long prevMillis = 0;
long interval = 12;
int CSPIN = 45;
int smooth = 0; // control interpolation/smoothing
libHubsan hubsan;
libA7105 a7105;
int pc = SCK;
void setup() {
  // Initialize Serial comms
  Serial.begin(115200);
  Serial.println("Hubsan X4 H107D Quadcopter Controller for Arduino Mega");
  Serial.println("Revision: " + String(rev));
  
  
  // Commence Hubsan Binding procedure.
  Serial.println("** Initializing Transceiver **");
  // hubsan.init(CSPIN);
  // Serial.println("** Commencing Bind Choreography **");
  // hubsan.bind();
  // Serial.println("** Status: READY. **");
  SPI.begin();    
  byte a1 = 0xB5;
  byte a2 = 0xC5;
  a2 = SPI.transfer(a1);
  Serial.println(digitalRead(MOSI));
  Serial.println(digitalRead(MISO));
  Serial.println(a2, HEX);
  SPI.end();
}

void loop() {
  // a7105.setupA7105(CSPIN);
  // byte a;
  // a = SPI.transfer(0xB);
  // Serial.println(a, HEX);
  // a = SPI.transfer(0);
  // Serial.println(a, HEX);
  // a = SPI.transfer(0);
  // Serial.println(a, HEX);
  // a = SPI.transfer(0);
  // Serial.println(a, HEX);
  // a = SPI.transfer(0);
  // Serial.println(a, HEX);
  delay(10000);
}

// void updateControlPacket() {
//   if (smooth == 0) {
//     controlpacket[2] = controlbuffer[0]; // Elevation
//     controlpacket[4] = controlbuffer[1]; // Yaw
//     controlpacket[6] = controlbuffer[2]; // Pitch
//     controlpacket[8] = controlbuffer[3]; // Roll
//   }
//   else {
//     smoothbuffer[0] = controlbuffer[0];
//     smoothbuffer[1] = byte(int(smoothbuffer[1]) + ((int(smoothbuffer[1])-int(controlbuffer[1]))/2));
//     smoothbuffer[2] = byte(int(smoothbuffer[2]) + ((int(smoothbuffer[2])-int(controlbuffer[2]))/2));
//     smoothbuffer[3] = byte(int(smoothbuffer[3]) + ((int(smoothbuffer[3])-int(controlbuffer[3]))/2));

//     controlpacket[2] = smoothbuffer[0]; // Elevation
//     controlpacket[4] = smoothbuffer[1]; // Yaw
//     controlpacket[6] = smoothbuffer[2]; // Pitch
//     controlpacket[8] = smoothbuffer[3]; // Roll
//   }
// }

// void sendControlPacket() {
//   hubsan.getChecksum(controlpacket);
//   hubsan.txPacket(controlpacket);
// }

// void toggleSmoothing() {
//   if (smooth == 0){
//     smooth = 1;
//     Serial.println("Smoothing enabled.");
//   }
//   else {
//     smooth = 0;
//     Serial.println("Smoothing disabled.");
//   }
// }

