import cv2
import numpy as np
import matplotlib.pyplot as plt

def otsu_parameters(gray):
    hist = cv2.calcHist([gray], [0], None, [256], [0, 256]).ravel()
    total_pixels = gray.size

    prob = hist / total_pixels

    omega = np.cumsum(prob)                   
    mu = np.cumsum(prob * np.arange(256))      
    mu_t = mu[-1]                              

    sigma_b2 = (mu_t * omega - mu) ** 2 / (omega * (1 - omega) + 1e-10)

    k_star = np.argmax(sigma_b2)
    max_sigma_b2 = sigma_b2[k_star]
    sigma_t2 = np.sum(((np.arange(256) - mu_t) ** 2) * prob)

    eta = max_sigma_b2 / sigma_t2

    return k_star, max_sigma_b2, eta, hist

gray = cv2.imread('images/top-dividend-stocks.jpg', cv2.IMREAD_GRAYSCALE)

if gray is None:
    print("Error: Unable to load image.")
    exit()

k_star, sigma_b2, eta, hist = otsu_parameters(gray)

_, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

print("Otsu Thresholding Results:")
print(f"Optimal Threshold (k*): {k_star}")
print(f"Between-Class Variance (σ_B²): {sigma_b2:.4f}")
print(f"Efficiency Metric (η): {eta:.4f}")


plt.figure(figsize=(12, 8))

plt.subplot(2, 2, 1)
plt.imshow(gray, cmap='gray')
plt.title('Input Grayscale Image')
plt.axis('off')

plt.subplot(2, 2, 2)
plt.plot(hist, color='black')
plt.title('Histogram of Input Image')
plt.xlabel('Intensity Level')
plt.ylabel('Frequency')

plt.subplot(2, 2, 3)
plt.imshow(binary, cmap='gray')
plt.title(f'Segmented Image (k* = {k_star})')
plt.axis('off')

plt.subplot(2, 2, 4)
plt.plot(hist, color='black')
plt.axvline(x=k_star, color='red', linestyle='--', label=f'Threshold = {k_star}')
plt.title('Histogram with Optimal Threshold')
plt.xlabel('Intensity Level')
plt.ylabel('Frequency')
plt.legend()

plt.tight_layout()
plt.show()