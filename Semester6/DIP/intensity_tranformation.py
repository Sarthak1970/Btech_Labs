import cv2
import numpy as np

class Image_Negative:
    def __init__(self,maxval=255):
        self.maxval=maxval

    def apply(self,img):
        return self.maxval-img


class Log_Transform:
    def __init__(self,c=1.0):
        self.c=c

    def apply(self, img):
        img_float = img.astype(np.float32)
        log_img = self.c * np.log1p(img_float)

        log_img = cv2.normalize(log_img, None, 0, 255, cv2.NORM_MINMAX)
        return log_img.astype(np.uint8)

class PowerLawTransform:
    def __init__(self, gamma=1.0):
        self.gamma = gamma

    def apply(self, img):
        img_norm = img / 255.0
        power_img = np.power(img_norm, self.gamma)
        return np.uint8(power_img * 255)

img=cv2.imread("pexels-okcode-2150281490-35381580.jpg",cv2.IMREAD_GRAYSCALE)
img=cv2.resize(img,(640,480))

gamma_transform = PowerLawTransform(gamma=0.5)
imgnegative_trans=Image_Negative()
powerlaw=PowerLawTransform()

gamma = gamma_transform.apply(img)
neg = imgnegative_trans.apply(img)
powerlaw = powerlaw.apply(img)

cv2.imshow("Original",img)
cv2.imshow("Gamma Transform",gamma)
cv2.imshow("Negative Transform",neg)
cv2.imshow("PowerLaw Transform",powerlaw)
cv2.waitKey(0)
cv2.destroyAllWindows()