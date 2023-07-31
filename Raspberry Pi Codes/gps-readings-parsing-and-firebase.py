import serial
import time
import string
import pynmea2

from firebase import firebase

# Firebase configuration
firebase_url = 'https://temp-40404-default-rtdb.firebaseio.com/'
firebase_secret = 'IFCWCqA6tULq3dbg2N2IMosVwdDaUDQU8qz714Uq'
firebase_app = firebase.FirebaseApplication(firebase_url, None)

latitude = 51.15043718
longitude = -114.03067890333334

port = "/dev/ttyUSB1"
#port = "COM6"
ser=serial.Serial(port, baudrate=9600, timeout=0.5)

while True:
    newdata=ser.readline().decode('utf-8')
    #print(newdata)
    #newdata="$GPRMC,203522.00,A,5109.0262308,N,11401.8407342,W,0.004,133.4,130522,0.0,E,D*2B"
    if newdata[0:6] == "$GPRMC":
        newmsg=pynmea2.parse(newdata)
        print(newmsg)
        lat=newmsg.latitude
        lng=newmsg.longitude
        if lng != 0 and lat != 0:
            data = {
            'longitude': lng,
            'latitude': lat,
            'status': "valid"
            }
            response = firebase_app.patch('/Database/lib20', data)
            print('Data sent to Firebase:', response)
