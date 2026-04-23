import cv2
import numpy as np
import matplotlib.pyplot as plt

def Hard_Thresholding(gray):
    t = 50
    img = gray.copy()
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            if img[i][j] > t:
                img[i][j] = 255
            else:
                img[i][j] = 0
    print("Hardcoded Threshold :" ,t)
    return img

def otsu(gray):
    hist = cv2.calcHist([gray],[0],None,[256],[0,256])
    total = gray.size

    best_t = 0
    best_var = 0

    for t in range(256):
        w0 = np.sum(hist[:t]) / total
        w1 = np.sum(hist[t:]) / total

        if w0 == 0 or w1 == 0:
            continue

        m0 = np.sum(np.arange(t) * hist[:t]) / (np.sum(hist[:t]) )
        m1 = np.sum(np.arange(t,256) * hist[t:]) / (np.sum(hist[t:]) )

        var = w0 * w1 * (m0 - m1) ** 2

        if var > best_var:
            best_var = var
            best_t = t

    img = gray.copy()
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            if img[i][j] > best_t:
                img[i][j] = 255
            else:
                img[i][j] = 0

    print("Otsu's Threshold :" ,best_t)

    return img

gray = cv2.imread('image.jpg', cv2.IMREAD_GRAYSCALE)
hard = Hard_Thresholding(gray)
otsu_img = otsu(gray)

plt.subplot(1,3,1)
plt.imshow(gray,cmap='gray')
plt.title('original')

plt.subplot(1,3,2)
plt.imshow(hard,cmap='gray')
plt.title('hard')

plt.subplot(1,3,3)
plt.imshow(otsu_img,cmap='gray')
plt.title('otsu')
plt.show()