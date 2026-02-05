import cv2
import numpy as np
import matplotlib.pyplot as plt


class HistogramEqualizerGray:

    def __init__(self, image_path):
        self.image = cv2.imread(image_path)

        if self.image is None:
            raise ValueError("Image not found!")

        self.L = 256

    def compute_histogram(self, channel):
        hist = np.zeros(self.L)

        for pixel in channel.flatten():
            hist[pixel] += 1

        return hist

    def compute_pdf(self, hist):
        return hist / self.image.size

    def compute_cdf(self, pdf):
        cdf = np.zeros_like(pdf)
        cumulative = 0

        for i in range(len(pdf)):
            cumulative += pdf[i]
            cdf[i] = cumulative

        return cdf

    def equalize(self):
        hist = self.compute_histogram(self.image)
        pdf = self.compute_pdf(hist)
        cdf = self.compute_cdf(pdf)

        mapping = np.floor((self.L - 1) * cdf).astype(np.uint8)

        equalized = mapping[self.image]

        return equalized

    def show_results(self):
        equalized = self.equalize()

        cv2.imshow("Equalized Grayscale", equalized)
        cv2.imshow("Original Grayscale", self.image)

        plt.figure()
        plt.hist(self.image.flatten(), bins=256)
        plt.title("Original Histogram")

        plt.figure()
        plt.hist(equalized.flatten(), bins=256)
        plt.title("Equalized Histogram")

        plt.show()

        cv2.waitKey(0)
        cv2.destroyAllWindows()

processor = HistogramEqualizerGray("imgs/WhatsApp Image 2026-02-05 at 1.11.05 PM (1).jpeg")
processor.show_results()
