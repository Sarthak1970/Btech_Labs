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


def manual_histogram(channel):
    hist = np.zeros(256)
    for value in channel.flatten():
        hist[int(value)] += 1
    return hist


def show_histogram(image, title):
    colors = ['r', 'g', 'b']
    plt.figure()
    for i, c in enumerate(colors):
        hist = manual_histogram(image[:, :, i])
        plt.plot(hist, color=c)
    plt.title(title)
    plt.xlabel("Intensity")
    plt.ylabel("Frequency")
    plt.show()


img = cv2.imread("images/top-dividend-stocks.jpg")

if img is None:
    raise ValueError("Image path incorrect")

img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

data = pd.read_excel("images/HistogramSpecificationData.xlsx", header=None)

target_R = pd.to_numeric(data.iloc[:, 0], errors='coerce').to_numpy()
target_G = pd.to_numeric(data.iloc[:, 1], errors='coerce').to_numpy()
target_B = pd.to_numeric(data.iloc[:, 2], errors='coerce').to_numpy()

if len(target_R) != 256:
    raise ValueError("Histogram must contain 256 rows")

R, G, B = cv2.split(img)

R_spec = HistogramSpecification(R, target_R).run()
G_spec = HistogramSpecification(G, target_G).run()
B_spec = HistogramSpecification(B, target_B).run()

specified_img = cv2.merge([R_spec, G_spec, B_spec])

R_eq = cv2.equalizeHist(R)
G_eq = cv2.equalizeHist(G)
B_eq = cv2.equalizeHist(B)

equalized_img = cv2.merge([R_eq, G_eq, B_eq])

plt.figure(figsize=(15,5))

plt.subplot(1,3,1)
plt.imshow(img)
plt.title("Original")
plt.axis("off")

plt.subplot(1,3,2)
plt.imshow(equalized_img)
plt.title("Equalized")
plt.axis("off")

plt.subplot(1,3,3)
plt.imshow(specified_img)
plt.title("Specified")
plt.axis("off")

plt.show()

show_histogram(img, "Original Histogram")
show_histogram(equalized_img, "Equalized Histogram")
show_histogram(specified_img, "Specified Histogram")
