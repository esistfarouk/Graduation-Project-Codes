import serial
import json
import vosk
import pyaudio
import RPi.GPIO as GPIO
import time

model_path = "vosk-model-small-en-us-0.15"  # path to the Vosk model directory
sample_rate = 16000   # audio sample rate

# Serial communication setup
ser = serial.Serial("/dev/ttyS0", 9600)    # Open port with baud rate

# Control commands
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

# GPIO setup for push button
button_pin = 12
GPIO.setmode(GPIO.BOARD)
GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(16, GPIO.OUT, initial=0)
GPIO.setup(18, GPIO.OUT, initial=0)


# Create a Vosk recognizer object
vosk_model = vosk.Model(model_path)
vosk_recognizer = vosk.KaldiRecognizer(vosk_model, sample_rate)

# Create a PyAudio object for recording audio from the microphone
pa = pyaudio.PyAudio()
stream = None  # Initialize stream as None

# Variable to keep track of recording state
is_recording = False

# Function to start/stop recording based on button state
def toggle_recording(channel):
    ser.write(stop)
    global is_recording, stream
    if not is_recording:
        GPIO.output(18,1)
        print("Recording started...")
        start_time = time.time()
        audio_data = b""
        stream = pa.open(format=pyaudio.paInt16, channels=1, rate=sample_rate, input=True, frames_per_buffer=8000)
        while time.time() - start_time < 3:  # Record for 3 seconds
            data = stream.read(4000)  # Read audio data from the microphone
            audio_data += data
        GPIO.output(18,0)
        is_recording = True
        # Pass the recorded audio data to the Vosk recognizer
        if vosk_recognizer.AcceptWaveform(audio_data):
            result = json.loads(vosk_recognizer.Result())
            text = result["text"]
            print("Recognized:", text)
            # Check if the recognized speech matches one of the target words
            if text == "right":
                print("Right")
                ser.write(right)
            elif text == "left" or text == "lift":
                print("Left")
                ser.write(left)
            elif text == "go forward":
                print("Forward")
                ser.write(forward)
            elif text == "go back":
                print("Backward")
                ser.write(backward)
            elif text == "stop":
                print("Stop")
                ser.write(stop)
            else:
                print("Unrecognized word")
                ser.write(stop)
        stream.stop_stream()
        stream.close()
        is_recording = False
        print("Recording stopped...")

# Register the button callback
GPIO.add_event_detect(button_pin, GPIO.FALLING, callback=toggle_recording, bouncetime=200)

# Loop to continuously recognize speech
while True:
    time.sleep(0.01)
