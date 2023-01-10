import serial.tools.list_ports
import account

class ACTUATOR:
	LED1 = 1
	LED2 = 2
	LIST = ["LED1", "LED2"]

#LOCAL FLAG
counter = 10
execute = 0
status 	= 0


def timerSet(time):
	global counter
	global execute

	counter = time

def timerRun():
	global counter
	global execute
	counter -=1
	if (counter == 0):
		execute = 1;

def timerOut():
	global execute
	if (execute == 1):
		execute = 0
		return 1
	else: return 0


def getPort():
	ports = serial.tools.list_ports.comports()
	N = len(ports)

	for i in range(0,N):
		port = ports[i]
		strPort = str(port)
		if "USB Serial Device" in strPort:
			splitPort = strPort.split(" ")
			comPort = (splitPort[0])
	#return comPort
	return "COM9"

mess=""
def readSerial(client):
	global mess

	sensor_infor = {};
	bytesToRead = ser.inWaiting()
	if (bytesToRead > 0):
		mess = mess + ser.read(bytesToRead).decode("UTF-8")
		while ('*' in mess) and ('/' in mess):
			start = mess.find('*')
			end = mess.find('/')
			temp = processData(client, mess[start:end+1]).split(":")
			sensor_infor[temp[0]] = temp[1]

			if (end == len(mess)):
				mess = "" 
			else:
				mess = mess[end+1:] 
		return sensor_infor

def writeSerial(actuator_infor):
	for actuator in ACTUATOR.LIST:
		if (actuator in actuator_infor):
			ser.write(str("*"+ actuator + ":"+actuator_infor[actuator]+"/").encode("UTF8"))

def processData(client,data):
	data = data.replace("*", "")
	data = data.replace("/", "")
	return data;

def sendCommand(command):
	print(command)
	ser.write(command.encode("UTF8"))

def getStatus():
	return status

def fsm():
	global status
	if (status==0): 
		sendCommand("!RST#")
		timerSet(10)
		status = 1
	elif (status == 1):
		if (timerOut()):
			status = 0
			sendCommand("!OK#")
	
if (getPort()!= "None"):
	ser = serial.Serial(port = getPort(), baudrate=9600)
	print(ser)



