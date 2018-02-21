/*
	Hubsan_H107L.h - Arduino Library for interfacing with the Hubsan X4 Quadcopter.
	Note: This lib is based on reverse-engineering work performed on the H107L "Improved"/V2 model.
	Created by James E. Hung, April 14, 2014. www.jimhung.com
*/

#ifndef libHubsan_H
#define libHubsan_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "libA7105.h"

void libHubsan_init(int cspin);
void libHubsan_bind();
void libHubsan_txPacket(byte *ppacket);
void libHubsan_rxPacket(byte *ppacket);
void libHubsan_getChecksum(byte *ppacket);
void libHubsan_printPacket(const char* msg, byte* packet);

byte _channel;
byte _sessionid[4];
byte _txpacket[16];
byte _rxpacket[16];


#endif