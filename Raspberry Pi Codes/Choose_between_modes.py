import os
import sys

import subprocess
import signal

import RPi.GPIO as GPIO

import serial
from time import sleep

GPIO.setmode(GPIO.BOARD)
GPIO.setup(16, GPIO.OUT, initial=0)
GPIO.setup(18, GPIO.OUT, initial=0)

flag_eye = 0
flag_voice = 0

ser = serial.Serial ("/dev/ttyS0", 9600)    #Open port with baud rate
command1 = b'eye\r'
command2 = b'voice\r'
welcome = "Raspberry on\r\n"
welcome = welcome.encode("utf-8")
ser.write(welcome)
while True:
  received_data = ser.read()              #read serial port
  sleep(0.03)
  data_left = ser.inWaiting()             #check for remaining byte
  received_data += ser.read(data_left)
  print (received_data)                   #print received data
  if received_data == command1:
    GPIO.output(18,0)
    GPIO.output(16,1)
    if flag_voice == 1:
      #l.terminate()
      subprocess.Popen(["pkill", "-f", "/home/pi/Desktop/voice/voice/voice-pushbutton.py"])
      flag_voice = 0
    if flag_eye != 1: 
      #p=subprocess.Popen( "python /home/pi/GazeTracking/example-1.py",shell=True,preexec_fn=os.setsid)
      subprocess.Popen(["python", "/home/pi/GazeTracking/example-1.py"])
      flag_eye = 1
  elif received_data == command2:
    GPIO.output(16,0)
    if flag_eye == 1:
      #p.terminate()
      subprocess.Popen(["pkill", "-f", "/home/pi/GazeTracking/example-1.py"])
      flag_eye = 0
    if flag_voice != 1:
      #l=subprocess.Popen( "python /home/pi/Desktop/voice/voice/voice-pushbutton.py",shell=True,preexec_fn=os.setsid)
      #l=subprocess.Popen( "python /home/pi/Desktop/voice/voice/voice.py",shell=True,preexec_fn=os.setsid)
      #l=subprocess.Popen( "python /home/pi/final_push_button.py",shell=True,preexec_fn=os.setsid)
      subprocess.Popen(["python", "/home/pi/Desktop/voice/voice/voice-pushbutton.py"])
      flag_voice = 1
  else:
    GPIO.output(16,0)
    GPIO.output(18,0)
    if flag_eye == 1:
      subprocess.Popen(["pkill", "-f", "/home/pi/GazeTracking/example-1.py"])
      flag_eye = 0
    if flag_voice == 1:
      subprocess.Popen(["pkill", "-f", "/home/pi/Desktop/voice/voice/voice-pushbutton.py"])
      flag_voice = 0

