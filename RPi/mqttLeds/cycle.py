import paho.mqtt.client as mqtt
import sys
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

blue = 18
red = 19
green = 13

GPIO.setup(blue, GPIO.OUT)

pBlue = GPIO.PWM(blue, 100);
pBlue.start(0);

broker_addr="192.168.10.105"
pwmTopic = "led/cycle"
client = mqtt.Client("RPiZeroCycle");
client.connect(broker_addr)
client.subscribe(pwmTopic)
client.publish(pwmTopic, "off")

running = False


def on_message(client, userdata, message):
	global running
        payload = str(message.payload.decode("utf-8"))
	#print("message received " ,payload)
	#print("message topic=",message.topic)
	if message.topic == pwmTopic:
		if payload == 'on':
			running = True
		else:
			running = False
	print("Running is : ", running)


client.on_message=on_message
client.loop_start()

try:
	while True:
		while running:
			for dc in range(0,101,1):
				pBlue.ChangeDutyCycle(dc)
				time.sleep(0.1)
			for dc in range(100,-1,-1):
				pBlue.ChangeDutyCycle(dc)
				time.sleep(0.1)
except KeyboardInterrupt:
	pass
pBlue.stop()

