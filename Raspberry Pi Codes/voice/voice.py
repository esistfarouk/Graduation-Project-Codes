import RPi.GPIO as GPIO
import serial
import os
import json
import vosk
import pyaudio
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)


model_path = "vosk-model-small-en-us-0.15"  # path to the Vosk model directory
sample_rate = 16000   # audio sample rate

ser = serial.Serial ("/dev/ttyS0", 9600)    #Open port with baud rate


forward = "Forward\r\n"
forward = forward.encode("utf-8")
backward = "Backward\r\n"
backward = backward.encode("utf-8")
right = "Right\r\n"
right = right.encode("utf-8")
left = "Left\r\n"
left = left.encode("utf-8")
stop = "Stop\r\n"
stop = stop.encode("utf-8")


# create a Vosk recognizer object
vosk_model = vosk.Model(model_path)
vosk_recognizer = vosk.KaldiRecognizer(vosk_model, sample_rate)

# create a PyAudio object for recording audio from the microphone
pa = pyaudio.PyAudio()
stream = pa.open(format=pyaudio.paInt16, channels=1, rate=sample_rate, input=True, frames_per_buffer=8000)

# loop to continuously recognize speech
while True:
        data = stream.read(4000)  # read audio data from the microphone
        if len(data) == 0:
            break
        if vosk_recognizer.AcceptWaveform(data):
            # get the recognized speech from the recognizer object
            result = json.loads(vosk_recognizer.Result())
            text = result["text"]
            # check if the recognized speech matches one of the target words
            if text == "right":
                print("Right")
                ser.write(right)
            elif text == "left" or text == "lift":
                print("Left")
                ser.write(left)
            elif text == "go forward":
                print("Forward")
                ser.write(forward)
            elif text == "go back" or text == "no back":
                print("Backward")
                ser.write(backward)
            elif text == "stop":
                print("Stop")
                ser.write(stop)
            else:
                print(text)
                ser.write(stop)
