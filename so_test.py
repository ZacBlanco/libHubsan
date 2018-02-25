#! /usr/bin/env python3
from ctypes import *
import sys, termios, tty, os, time
# getch adapted from https://github.com/recantha/EduKit3-RC-Keyboard/blob/master/rc_keyboard.py

hubsan = cdll.LoadLibrary('bin/libhubsan.so')

rev = 1 # revision
controlbuffer = bytearray(b''.join([b'\x00']*4))
smoothbuffer = bytearray(b''.join([b'\x00']*4))
controlpacket = bytearray(b''.join([b'\x00']*16))

prevMillis = 0
interval = float(12)/1000
lps = 1000
smooth = 0
#libhubsan hubsan

THROTTLE = 0
PITCH = 128
YAW = 128
ROLL = 128

def reset_position():
	PITCH = 128
	YAW = 128
	ROLL = 128

def setup():
	global hubsan, rev, controlbuffer, smoothbuffer, controlpacket, prevMillis, interval, smooth,THROTTLE, PITCH, YAW, ROLL
	print("set up control packet structure")
	#for i in range(16):
	#	controlpacket[i] = 0 
	controlpacket[0] = int.from_bytes(b'\x20', 'big')
	controlpacket[9] = int.from_bytes(b'\x0A', 'big')
	controlpacket[10] = int.from_bytes(b'\x19', 'big')

	# hardcoded initial trim 
	controlpacket[4] = int.from_bytes(b'\x80', 'big')
	controlpacket[6] = int.from_bytes(b'\x80', 'big') # manual trim
	controlpacket[8] = int.from_bytes(b'\x80', 'big') # manual trim

	print("Initializing transiever")
	hubsan.libHubsan_init(0)
	print("Commencing Bind Choreography")
	hubsan.libHubsan_bind()
	print(" Status READY ")
	return

def getch():
	fd = sys.stdin.fileno()
	old_settings = termios.tcgetattr(fd)
	try:
		tty.setraw(sys.stdin.fileno())
		ch = sys.stdin.read(1)
		return ch 
	finally:
		termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
	return 
 
 
def loop():
	global hubsan, rev, controlbuffer, smoothbuffer, controlpacket, prevMillis, interval, smooth,THROTTLE, PITCH, YAW, ROLL, lps
	button_delay = 0.0001
	max_wait = float(1)/lps
	while True:
		print("running getch")
		char = getch()
		print("Finished getch")
		print(char)

		ct = time.time()
		if (char == "q"):
			print("QUITTING")
			break;
			time.sleep(button_delay)

		if (char == "a"):
			print("Roll left")
			ROLL+= 5
			time.sleep(button_delay)
		
		elif (char == "d"):
			print("Roll right")
			ROLL -= 5
			time.sleep(button_delay)
		
		elif (char == "w"):
			print("Throttle up")
			THROTTLE += 5
			time.sleep(button_delay)
		
		elif (char == "s"):
			print("Throttle down")
			THROTTLE -= 5
			time.sleep(button_delay)

		elif (char == "i"):
			print("Pitch forward")
			PITCH -= 5
			time.sleep(button_delay)
		
		elif (char == "k"):
			print("Pitch back")
			PITCH += 5
			time.sleep(button_delay)
		
		elif (char == "j"):
			print("Yaw turn left")
			YAW -= 5
			time.sleep(button_delay)
		
		elif (char == "l"):
			print("Yaw turn right")
			YAW += 5
			time.sleep(button_delay)
		nt = time.time()
		pt = nt - ct
		if (pt < max_wait):
			time.sleep(max_wait-pt)
		print("update cp")
		updateControlPacket()
		print('updated control packet')
		sendControlPacket()
		print('sent control packet')

	

def updateControlPacket():
	global hubsan, rev, controlbuffer, smoothbuffer, controlpacket, prevMillis, interval, smooth,THROTTLE, PITCH, YAW, ROLL
	controlbuffer[0] = THROTTLE
	controlbuffer[1] = YAW
	controlbuffer[2] = PITCH
	controlbuffer[3] = ROLL
	
	if(smooth == 0):
		controlpacket[2] = controlbuffer[0]
		controlpacket[4] = controlbuffer[1]
		controlpacket[6] = controlbuffer[2]
		controlpacket[8] = controlbuffer[3]
	return
		

def sendControlPacket():
	global hubsan, rev, controlbuffer, smoothbuffer, controlpacket, prevMillis, interval, smooth,THROTTLE, PITCH, YAW, ROLL
	print(controlpacket)
	cp = c_char_p(bytes(controlpacket))
	hubsan.libHubsan_getChecksum(cp)
	#print_pkt(cp)
	hubsan.libHubsan_txPacket(cp)
	reset_position()
	return

def toggleSmoothing():
	pass

def print_pkt(cp):
	for i in range(16):
		print('ay')
		print(cp + i)

if __name__ == "__main__":
	setup()
	loop()


