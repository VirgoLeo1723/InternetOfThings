from keras.models import load_model
from PIL import Image, ImageOps
import time
import numpy as np
import cv2 as cv
import sys
import random
import account

#DEFINE
LABELS = {0 :"Mask on",
		 1 :"Mask off",
		 2 :"Other",
		}

#LOCAL FLAG
counter = 7
execute = 0
status 	= 0

# Load the model
model = load_model('ai_model/keras_model.h5')
data = np.ndarray(shape=(1, 224, 224, 3), dtype=np.float32)
cam = cv.VideoCapture(0)

def image_capture():
   ret,frame = cam.read()
   cv.imwrite ("image/test.png",frame)

def image_detect():
	image = Image.open('image/test.png')
	size = (224, 224)
	image = ImageOps.fit(image, size, Image.ANTIALIAS)

	image_array = np.asarray(image)
	normalized_image_array = (image_array.astype(np.float32) / 127.0) - 1
	data[0] = normalized_image_array
	prediction = model.predict(data)

	maxindex = 0
	maxvalue = 0
	for index,value in enumerate(prediction[0]):
		if (maxvalue<value) :
			maxvalue = value
			maxindex = index
	return maxindex

def timerSet(time):
	global counter
	global execute

	counter = time
	execute = 1

def timerRun():
	global counter
	global status
	counter -=1;
	if (counter == 0):
		timerSet(7)

def executed():
	global execute

	if (execute==0): return 1
	else: execute = 0

	return 0

def fsm():
	if (executed()==0):
		image_capture()
		value = LABELS[image_detect()]
		account.client.publish(account.ADA.DETECT_FEED["DETC"], value)


