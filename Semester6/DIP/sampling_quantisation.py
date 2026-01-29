import cv2 
import numpy as np
import matplotlib.pyplot as plt

img=cv2.imread("pexels-okcode-2150281490-35381580.jpg")

h,w,c=img.shape
print(h,w,c)


sampling_factor=16
sampled_img = img[::sampling_factor, ::sampling_factor]

sh,sw,sc=sampled_img.shape
print(sh,sw,sc)

levels = 4 
quantised_img = np.floor(img / (256 / levels)) * (256 / levels)
quantised_img = quantised_img.astype(np.uint8)

qh,qw,qc=quantised_img.shape
print(qh,qw,qc)

img=cv2.resize(img,(640,480))
sampled_img=cv2.resize(sampled_img,(640,480))
quantised_img=cv2.resize(quantised_img,(640,480))

cv2.imshow('Original (4160 x 6240 x 3)', img)
cv2.imshow('Sampled (260 x 390 x 3)',sampled_img)
cv2.imshow('Quantized',quantised_img)
cv2.waitKey(0)
cv2.destroyAllWindows()