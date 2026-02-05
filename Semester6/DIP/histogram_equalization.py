import cv2 
import numpy as np
import matplotlib.pyplot as plt

img = cv2.imread("imgs/pexels-okcode-2150281490-35381580.jpg")

class Histogram_Equalizer:

    def __init__(self, image):
        if image is None:
            raise ValueError("Image not found!")

        self.image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        self.L = 256

    def compute_histogram(self, channel):
        hist = np.zeros(self.L, dtype=int)
        for pixel in channel.flatten():
            hist[pixel] += 1
        return hist

    def compute_pdf(self, hist, total_pixels):
        return hist / total_pixels

    def compute_cdf(self, pdf):
        cdf = np.zeros_like(pdf)
        cumulative = 0
        for i in range(len(pdf)):
            cumulative += pdf[i]
            cdf[i] = cumulative
        return cdf

    def equalize_channel(self, channel):
        hist = self.compute_histogram(channel)
        pdf = self.compute_pdf(hist, channel.size)
        cdf = self.compute_cdf(pdf)

        mapping = np.floor((self.L - 1) * cdf).astype(np.uint8)

        equalized_channel = mapping[channel]
        return equalized_channel

    def equalize_image(self):
        r, g, b = cv2.split(self.image)

        r_eq = self.equalize_channel(r)
        g_eq = self.equalize_channel(g)
        b_eq = self.equalize_channel(b)

        equalized_img = cv2.merge((r_eq, g_eq, b_eq))
        return equalized_img, (r, g, b), (r_eq, g_eq, b_eq)

    def show_results(self):
        equalized_img, original_channels, equalized_channels = self.equalize_image()

        input_bgr = cv2.cvtColor(self.image, cv2.COLOR_RGB2BGR)
        equalized_bgr = cv2.cvtColor(equalized_img, cv2.COLOR_RGB2BGR)

        input_bgr=cv2.resize(input_bgr,(640,480))
        equalized_bgr=cv2.resize(equalized_bgr,(640,480))

        cv2.imshow("Input Image", input_bgr)
        cv2.imshow("Histogram Equalized Image", equalized_bgr)

        colors = ['Red', 'Green', 'Blue']

        for ch, color in zip(original_channels, colors):
            plt.figure()
            plt.hist(ch.flatten(), bins=256)
            plt.title(f"{color} Histogram - Input")
            plt.xlabel("Intensity")
            plt.ylabel("Frequency")

        for ch, color in zip(equalized_channels, colors):
            plt.figure()
            plt.hist(ch.flatten(), bins=256)
            plt.title(f"{color} Histogram - Equalized")
            plt.xlabel("Intensity")
            plt.ylabel("Frequency")

        plt.show()

        cv2.waitKey(0)
        cv2.destroyAllWindows()



he = Histogram_Equalizer(img)
he.show_results()
