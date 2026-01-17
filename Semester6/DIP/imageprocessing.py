import cv2 
import sys

img = cv2.imread("pexels-okcode-2150281490-35381580.jpg")

if img is None:
    sys.exit("Could not read the image.")

h,w,c=img.shape
print("Height:", h)
print("Width:", w)
print("Channels:", c)

resized=cv2.resize(img,(320,240))
gray = cv2.cvtColor(resized, cv2.COLOR_BGR2GRAY)
cv2.imshow("Display window", gray)
cv2.waitKey(0)
cv2.destroyAllWindows()
