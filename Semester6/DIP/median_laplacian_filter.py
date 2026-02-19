import cv2
import numpy as np

def median_filter(image, kernel_size=3):
    pad = kernel_size // 2
    h, w, c = image.shape
    
    padded = np.pad(image, ((pad, pad), (pad, pad), (0, 0)), mode='edge')
    output = np.zeros_like(image)
    
    for ch in range(c):
        for i in range(h):
            for j in range(w):
                window = padded[i:i+kernel_size, j:j+kernel_size, ch]
                output[i, j, ch] = np.median(window)
    
    return output

def laplacian_filter(image):
    kernel = np.array([
        [0, 1, 0],
        [1, -4, 1],
        [0, 1, 0]
    ])
    
    pad = 1
    h, w, c = image.shape
    
    padded = np.pad(image, ((pad, pad), (pad, pad), (0, 0)), mode='edge')
    laplacian = np.zeros_like(image, dtype=np.float32)
    
    for ch in range(c):
        for i in range(h):
            for j in range(w):
                region = padded[i:i+3, j:j+3, ch]
                laplacian[i, j, ch] = np.sum(region * kernel)
    
    return laplacian

def laplacian_sharpen(image):
    lap = laplacian_filter(image)
    sharpened = image.astype(np.float32) - lap
    sharpened = np.clip(sharpened, 0, 255)
    return sharpened.astype(np.uint8)

image = cv2.imread("images/imgnoise.png")

if image is None:
    print("Error: Image not found")
    exit()

median_output = median_filter(image, 3)

laplacian_output = laplacian_sharpen(image)

cv2.imshow("Original Image", image)
cv2.imshow("Median Filter Output", median_output)
cv2.imshow("Laplacian + Sharpened Output", laplacian_output)

cv2.waitKey(0)
cv2.destroyAllWindows()
