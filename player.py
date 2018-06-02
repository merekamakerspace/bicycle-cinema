import serial
import os
import sys
import random


strPort1 = '/dev/ttyACM0'
#strPort1 = '/dev/ttyACM1'

ser = serial.Serial(strPort1, 115200)

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    print "led on"
    client.publish(LED_TOPIC, 'ON')


LED_TOPIC = 'lab/light2/switch'

LIGHT_ON_CMD = "mqtt pub -h '192.168.0.30' -t 'lab/light2/switch' -m 'ON'"
LIGHT_OFF_CMD = "mqtt pub -h '192.168.0.30' -t 'lab/light2/switch' -m 'OFF'"

OMX_CMD = 'omxplayer -o alsa:hw:1,0 '
files = ['mereka.mp4', 'bike-gen.mp4', 'circular-economy.mp4']
fi = 0

playing = False

os.system(LIGHT_ON_CMD)
while True:

	#client.loop()
	line = ser.readline().strip()
	try:
		if len(line) > 0 and line[0] in ['R', 'S']:
			print line
		else:
			
			val = int(line)
			print val

			if val > 565:
				if not playing:
					print "Player movie"
					os.system(LIGHT_OFF_CMD)
					playing = True
					file  = files[fi]
					fi += 1
					if fi >= len(files):
						fi = 0
					os.system(OMX_CMD + file)
					os.system(LIGHT_ON_CMD)
								
		
			
	except KeyboardInterrupt:
		raise
	except:
		raise
		e = sys.exc_info()

		print "something messed up", e
		