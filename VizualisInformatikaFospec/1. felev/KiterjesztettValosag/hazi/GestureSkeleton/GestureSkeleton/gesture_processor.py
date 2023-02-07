import cv2
import math
import numpy as np
import mediapipe as mp
import sys
from google.protobuf.json_format import MessageToDict

mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
#help(mp_hands.Hands)

cameraIndex = int(sys.argv[1])
fileName = sys.argv[2]
WIDTH = int(sys.argv[3])
HEIGHT = int(sys.argv[4])

DESIRED_HEIGHT = 480
DESIRED_WIDTH = 480
def resize(image):
  h, w = image.shape[:2]
  img = image
  if h < w:
    img = cv2.resize(img, (DESIRED_WIDTH, math.floor(h/(w/DESIRED_WIDTH))))
  else:
    img = cv2.resize(img, (math.floor(w/(h/DESIRED_HEIGHT)), DESIRED_HEIGHT))
  return img

cap = cv2.VideoCapture(cameraIndex if cameraIndex >= 0 else fileName)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, WIDTH)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, HEIGHT)
frame_counter = 0
max_frame = cap.get(cv2.CAP_PROP_FRAME_COUNT)

# Run MediaPipe Hands.
with mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=2,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.7) as hands:

    while(cap.isOpened()):
      # Capture frame-by-frame
      ret, frame = cap.read()
      frame_counter += 1
      if frame_counter == max_frame:
        frame_counter = 0
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
      if ret == True:
        # Convert the BGR image to RGB, flip the image around y-axis for correct 
        # handedness output and process it with MediaPipe Hands.
        frame = cv2.flip(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB), 1)

        frame.flags.writeable = False
        results = hands.process(frame)
        frame.flags.writeable = True

        # Print handedness (left v.s. right hand).
        if results.multi_handedness != None and results.multi_hand_landmarks != None:
          for count, res in enumerate(results.multi_handedness):
            #print(f'{res.classification[0].index}, {res.classification[0].score}, {res.classification[0].label}\n')
            label = MessageToDict(res)['classification'][0]['label']
            print(f'D,{label}');
            print
            for i in range(0, 21):
              print(f'{results.multi_hand_landmarks[count].landmark[i].x},{results.multi_hand_landmarks[count].landmark[i].y},{results.multi_hand_landmarks[count].landmark[i].y}\n')

        annotated_image = frame.copy()
        if results.multi_hand_landmarks:
            # Draw hand landmarks of each hand.
            image_hight, image_width, _ = frame.shape
            for hand_landmarks in results.multi_hand_landmarks:
              mp_drawing.draw_landmarks(
                  annotated_image, hand_landmarks, mp_hands.HAND_CONNECTIONS,
                  mp_drawing_styles.get_default_hand_landmarks_style(),
                  mp_drawing_styles.get_default_hand_connections_style())
        img = resize(cv2.flip(annotated_image, 1))

        # Display the resulting frame
        cv2.imshow('Frame',img)
        sys.stdout.flush()

        # Press Q on keyboard to  exit
        if cv2.waitKey(25) & 0xFF == ord('q'):
          break

      # Break the loop
      else: 
        break

# When everything done, release the video capture object
cap.release()
# Closes all the frames
cv2.destroyAllWindows() 
