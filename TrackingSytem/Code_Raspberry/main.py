import sys
import random
import time


import account
import sensor
import ai 
import button
import urart

from Adafruit_IO import MQTTClient


account.client.connect();
account.client.loop_background()
infor = None

while True:
    # ai.timerRun()
    # ai.fsm()

    # try:
    #     urart.timerRun()
    #     urart.fsm()
    #     infor = urart.readSerial(account.client)
    # except:
    #     pass

    # if (urart.getStatus()==0):
    #     if (infor != None):
    #         sensor.sendImediate(infor)

    actuator_ctrl = account.savedControlMessage()
    if (len(actuator_ctrl) > 0 ):
        urart.writeSerial(actuator_ctrl)
        account.resetControlMessage()

    time.sleep(1)
    
