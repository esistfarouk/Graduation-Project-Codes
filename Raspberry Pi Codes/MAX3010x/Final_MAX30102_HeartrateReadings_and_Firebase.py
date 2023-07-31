from heartrate_monitor import HeartRateMonitor
import time

from firebase import firebase

# Firebase configuration
firebase_url = 'https://temp-40404-default-rtdb.firebaseio.com/'
firebase_secret = 'IFCWCqA6tULq3dbg2N2IMosVwdDaUDQU8qz714Uq'
firebase_app = firebase.FirebaseApplication(firebase_url, None)


hrm = HeartRateMonitor()
hrm.start_sensor()

start_time = time.time()
interval = 5  # Interval in seconds
bpm_values = []
spo2_values = []

while True:
	current_time = time.time()

	# Check if 10 seconds have passed
	if current_time - start_time >= interval:
		# Calculate average over the interval
		if len(bpm_values) > 0 and len(spo2_values) > 0:
			average_bpm = sum(bpm_values) / len(bpm_values)
			average_spo2 = sum(spo2_values) / len(spo2_values)

			# Print or use the average values as needed
			print(f"Average heart rate over {interval} seconds: {average_bpm} bpm")
			print(f"Average SpO2 over {interval} seconds: {average_spo2}%")
			data = {
			'heart': average_bpm,
			'oxygen': average_spo2
			}
			response = firebase_app.patch('/Database/lib20', data)
			print('Data sent to Firebase:', response)

		# Reset the start time and clear the values list
		start_time = time.time()
		bpm_values = []
		spo2_values = []

	# Access the values
	bpm = hrm.get_bpm()
	valid_bpm = hrm.is_bpm_valid()
	spo2 = hrm.get_spo2()
	valid_spo2 = hrm.is_spo2_valid()

	# Accumulate the values
	if valid_bpm:            
		bpm_values.append(bpm)
	if valid_spo2:            
		spo2_values.append(spo2)
	time.sleep(0.1)


hrm.stop_sensor()
