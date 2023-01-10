import sys
import random
import time
from Adafruit_IO import MQTTClient

waitingMessage = ""
controlMessage = ""

#DEFINE
class ADA:
    SENSOR_FEED  = {"LIGHT": "lab1.sensor-light"        ,
                    "TEMP" : "lab1.sensor-temperature"  ,
                    "HUMD" : "lab1.sensor-humidity"     }

    BUTTON_FEED  = {"LED1" : "lab1.button-led1"         ,
                    "LED2" : "lab1.button-led2"         }
    DETECT_FEED =  {"DETC" : "lab1.detect"              }
    ERROR_FEED =   {"ERROR" : "lab1.error"             }

    GROUP    = "lab1"  
    USERNAME = "TrungNhat"
    KEY      = "aio_iYlL34xJ6n5I5fTezMETWCrFOyCf"


def connnected(client):
    for i in ADA.SENSOR_FEED:
        client.subscribe(ADA.SENSOR_FEED[i])

    for i in ADA.BUTTON_FEED:
        client.subscribe(ADA.BUTTON_FEED[i])

    for i in ADA.DETECT_FEED:
        client.subscribe(ADA.DETECT_FEED[i])

    for i in ADA.ERROR_FEED:
        client.subscribe(ADA.ERROR_FEED[i])

    print("Connected Successfully")

    # client.subscribe_group(ADA.GROUP)
    # print("Connected Successfully")

def subscribe(client, userdata, mid, granted_pos):
    print("Subscribe Successfully")

def disconnected(client):
    print("Disconnected")

def message(client, feed_id, payload):
    print(f"Take data from {feed_id}: " + payload)
    if feed_id == ADA.ERROR_FEED["ERROR"]:
        if payload=="waiting": client.publish("lab1.error","end")
        waitingMessage = payload
        print(waitingMessage)

    global controlMessage
    for actuator in ADA.BUTTON_FEED:
        if (ADA.BUTTON_FEED[actuator] == feed_id):
            controlMessage = {actuator:payload}

# Error hop controller
def isWaitingMessage():
    if waitingMessage=="waiting": return 1
    else: return 0

def resetWaitingMessage():
    global waitingMessage;
    waitingMessage=""

def savedControlMessage():
    return controlMessage

def resetControlMessage():
    global controlMessage
    controlMessage = {}


client = MQTTClient(ADA.USERNAME, ADA.KEY)

client.on_connect = connnected
client.on_disconnect = disconnected
client.on_message = message
client.on_subscribe = subscribe

