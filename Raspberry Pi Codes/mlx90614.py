import board
import busio as io
import adafruit_mlx90614

from time import sleep

from firebase import firebase

# Firebase configuration
firebase_url = 'https://temp-40404-default-rtdb.firebaseio.com/'
firebase_secret = 'IFCWCqA6tULq3dbg2N2IMosVwdDaUDQU8qz714Uq'
firebase_app = firebase.FirebaseApplication(firebase_url, None)


i2c = io.I2C(board.SCL, board.SDA, frequency=100000)
mlx = adafruit_mlx90614.MLX90614(i2c)

while True:
	try:
		ambientTemp = "{:.2f}".format(mlx.ambient_temperature)
		targetTemp = "{:.2f}".format(mlx.object_temperature)
		sleep(1)
		data = {'TEMP':mlx.object_temperature}
		response = firebase_app.patch('/Database/lib20', data)
		print('Data sent to Firebase:', response)
		print("Target Temperature:", targetTemp,"°C")
	except:
		print("Error")
