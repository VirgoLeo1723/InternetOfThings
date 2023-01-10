import sys
import random
import time
import account

#DEFINE
class SENSOR:
	RESET = 0
	LIGHT = 1
	TEMP  = 2
	HUMD  = 3
	LIST  = ["LIGHT", "TEMP", "HUMD"]



#LOCAL FLAG
counter = 10
execute = 0
status 	= 0


def timerSet(time):
	global counter
	global execute

	counter = time
	execute = 1

def timerRun():
	global counter
	global status
	counter -= 1;
	if (counter == 0):
		if (status == SENSOR.RESET):  	status = SENSOR.LIGHT
		elif (status == SENSOR.LIGHT): 	status = SENSOR.TEMP
		elif (status == SENSOR.TEMP): 	status = SENSOR.HUMD
		elif (status == SENSOR.HUMD): 	status = SENSOR.LIGHT
		timerSet(10)

def executed():
	global execute

	if (execute==0): return 1
	else: execute = 0
	return 0

def fsm():
	global counter
	global status
	
	value= random.randint(0,100)

	if (status == SENSOR.LIGHT and executed()==0): account.client.publish(account.ADA.SENSOR_FEED["LIGHT"], value)
	elif (status == SENSOR.TEMP  and executed()==0): account.client.publish(account.ADA.SENSOR_FEED["TEMP"], value)
	elif (status == SENSOR.HUMD  and executed()==0): account.client.publish(account.ADA.SENSOR_FEED["HUMD"], value)


def sendImediate(sensor_infor_queue):
	for sensor in SENSOR.LIST :
		if (sensor in sensor_infor_queue):
			account.client.publish(account.ADA.SENSOR_FEED[sensor], sensor_infor_queue[sensor])







