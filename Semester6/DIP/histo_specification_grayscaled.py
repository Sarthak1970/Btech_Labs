import cv2
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

class HistogramSpecification:

    def __init__(self, channel, target_histogram):
        self.channel = channel
        self.target_hist = target_histogram
        self.L = 256

    def compute_histogram(self, image):
        hist = np.zeros(self.L)
        for value in image.flatten():
            hist[int(value)] += 1
        return hist

    def normalize_histogram(self, hist):
        total_pixels = np.sum(hist)
        return hist / total_pixels

    def compute_cdf(self, pdf):
        cdf = np.zeros(self.L)
        cumulative = 0
        for i in range(self.L):
            cumulative += pdf[i]
            cdf[i] = cumulative
        return cdf

    def build_mapping(self, src_cdf, tgt_cdf):
        mapping = np.zeros(self.L)
        for i in range(self.L):
            diff = np.abs(src_cdf[i] - tgt_cdf)
            mapping[i] = np.argmin(diff)
        return mapping.astype(np.uint8)

    def apply_mapping(self, mapping):
        output = np.zeros_like(self.channel)
        rows, cols = self.channel.shape
        for i in range(rows):
            for j in range(cols):
                output[i, j] = mapping[self.channel[i, j]]
        return output

    def run(self):
        src_hist = self.compute_histogram(self.channel)
        src_pdf = self.normalize_histogram(src_hist)
        src_cdf = self.compute_cdf(src_pdf)

        tgt_pdf = self.normalize_histogram(self.target_hist)
        tgt_cdf = self.compute_cdf(tgt_pdf)

        mapping = self.build_mapping(src_cdf, tgt_cdf)
        return self.apply_mapping(mapping)


class HistogramEqualization:

    def __init__(self, channel):
        self.channel = channel
        self.L = 256

    def compute_histogram(self):
        hist = np.zeros(self.L)
        for value in self.channel.flatten():
            hist[int(value)] += 1
        return hist

    def run(self):
        hist = self.compute_histogram()
        pdf = hist / np.sum(hist)

        cdf = np.zeros(self.L)
        cumulative = 0
        for i in range(self.L):
            cumulative += pdf[i]
            cdf[i] = cumulative

        mapping = np.round((self.L - 1) * cdf).astype(np.uint8)

        output = np.zeros_like(self.channel)
        rows, cols = self.channel.shape

        for i in range(rows):
            for j in range(cols):
                output[i, j] = mapping[self.channel[i, j]]

        return output


def manual_histogram(channel):
    hist = np.zeros(256)
    for value in channel.flatten():
        hist[int(value)] += 1
    return hist


def show_gray_histogram(image, title):
    hist = manual_histogram(image)
    plt.figure()
    plt.plot(hist)
    plt.title(title)
    plt.xlabel("Intensity")
    plt.ylabel("Frequency")
    plt.show()


def show_combined_histograms(orig, equalized, specified):
    h1 = manual_histogram(orig) / np.sum(orig.size)
    h2 = manual_histogram(equalized) / np.sum(equalized.size)
    h3 = manual_histogram(specified) / np.sum(specified.size)

    plt.figure(figsize=(8,5))
    plt.plot(h1, label="Original")
    plt.plot(h2, label="Equalized")
    plt.plot(h3, label="Specified")
    plt.title("Combined Histogram Comparison")
    plt.xlabel("Intensity")
    plt.ylabel("Normalized Frequency")
    plt.legend()
    plt.show()


img = cv2.imread("images/top-dividend-stocks.jpg")

if img is None:
    raise ValueError("Image path incorrect")

img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

R, G, B = cv2.split(img)

gray = ((R.astype(np.float32) +
         G.astype(np.float32) +
         B.astype(np.float32)) / 3).astype(np.uint8)

equalized_gray = HistogramEqualization(gray).run()

data = pd.read_excel("images/HistogramSpecificationData.xlsx", header=None)
target_hist = pd.to_numeric(data.iloc[:, 0], errors='coerce').to_numpy()

if len(target_hist) != 256:
    raise ValueError("Histogram must contain 256 rows")

specified_gray = HistogramSpecification(gray, target_hist).run()

plt.figure(figsize=(15,5))

plt.subplot(1,3,1)
plt.imshow(gray, cmap='gray')
plt.title("Original Grayscale")
plt.axis("off")

plt.subplot(1,3,2)
plt.imshow(equalized_gray, cmap='gray')
plt.title("Equalized Grayscale")
plt.axis("off")

plt.subplot(1,3,3)
plt.imshow(specified_gray, cmap='gray')
plt.title("Specified Grayscale")
plt.axis("off")

plt.show()

show_gray_histogram(gray, "Original Histogram")
show_gray_histogram(equalized_gray, "Equalized Histogram")
show_gray_histogram(specified_gray, "Specified Histogram")

show_combined_histograms(gray, equalized_gray, specified_gray)
