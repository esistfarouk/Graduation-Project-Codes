import serial

from gaze_tracking import GazeTracking

ser = serial.Serial ("/dev/ttyS0", 9600)    #Open port with baud rate


# from picamera.array import PiRGBArray
# from picamera import PiCamera
# import time
import cv2
# initialize the camera and grab a reference to the raw camera capture
# camera = PiCamera()
# camera.resolution = (640, 480)
# camera.framerate = 10

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

gaze = GazeTracking()
webcam = cv2.VideoCapture(0)
webcam.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
webcam.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
webcam.set(cv2.CAP_PROP_FPS, 32)

while True:
    # We get a new frame from the webcam
    _, frame = webcam.read()

    # We send this frame to GazeTracking to analyze it
    gaze.refresh(frame)

    frame = gaze.annotated_frame()
    text = ""

    if gaze.is_blinking():
        print("Stop")
        text = "Blinking"
        ser.write(stop)
    elif gaze.is_right():
        print("Right")
        text = "Looking right"
        ser.write(right)
    elif gaze.is_left():
        print("Left")
        text = "Looking left"
        ser.write(left)
    elif gaze.is_center():
        print("Forward")
        text = "Looking center"
        ser.write(forward)
    else:
        ser.write(stop)
    frame = cv2.flip(frame,1)
    cv2.putText(frame, text, (90, 60), cv2.FONT_HERSHEY_DUPLEX, 1.6, (147, 58, 31), 2)

    left_pupil = gaze.pupil_left_coords()
    right_pupil = gaze.pupil_right_coords()
    cv2.putText(frame, "Left pupil:  " + str(left_pupil), (90, 130), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
    cv2.putText(frame, "Right pupil: " + str(right_pupil), (90, 165), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)

    cv2.imshow("Demo", frame)

    if cv2.waitKey(1) == 27:
        break
webcam.release()
cv2.destroyAllWindows()
