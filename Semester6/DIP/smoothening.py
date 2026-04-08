import cv2
import math
import numpy as np
import matplotlib.pyplot as plt

class ColorSmoothing:

    def __init__(self, path):
        self.img = cv2.imread(path)
        self.img = cv2.cvtColor(self.img, cv2.COLOR_BGR2RGB) / 255.0

        self.rows, self.cols, _ = self.img.shape

        self.R = self.img[:, :, 0]
        self.G = self.img[:, :, 1]
        self.B = self.img[:, :, 2]

        self.H = [[0]*self.cols for _ in range(self.rows)]
        self.S = [[0]*self.cols for _ in range(self.rows)]
        self.I = [[0]*self.cols for _ in range(self.rows)]

        self.Rf = [[0]*self.cols for _ in range(self.rows)]
        self.Gf = [[0]*self.cols for _ in range(self.rows)]
        self.Bf = [[0]*self.cols for _ in range(self.rows)]

        self.Hf = [[0]*self.cols for _ in range(self.rows)]
        self.Sf = [[0]*self.cols for _ in range(self.rows)]
        self.If = [[0]*self.cols for _ in range(self.rows)]

    def rgb_to_hsi(self):
        for i in range(self.rows):
            for j in range(self.cols):
                r = self.R[i][j]
                g = self.G[i][j]
                b = self.B[i][j]

                num = 0.5 * ((r - g) + (r - b))
                den = math.sqrt((r - g)**2 + (r - b)*(g - b)) + 1e-6

                theta = math.acos(num / den)

                if b <= g:
                    h = theta
                else:
                    h = 2*math.pi - theta

                h = h / (2*math.pi)

                s = 1 - (3 * min(r, g, b) / (r + g + b + 1e-6))
                i_val = (r + g + b) / 3

                self.H[i][j] = h
                self.S[i][j] = s
                self.I[i][j] = i_val

    def gaussian(self, channel):
        kernel = [
            [1,2,1],
            [2,4,2],
            [1,2,1]
        ]

        out = [[0]*self.cols for _ in range(self.rows)]

        for i in range(1, self.rows-1):
            for j in range(1, self.cols-1):
                sum_val = 0
                for x in range(-1, 2):
                    for y in range(-1, 2):
                        sum_val += channel[i+x][j+y] * kernel[x+1][y+1]

                out[i][j] = sum_val / 16

        return out

    def smooth_rgb(self):
        self.Rf = self.gaussian(self.R)
        self.Gf = self.gaussian(self.G)
        self.Bf = self.gaussian(self.B)

    def smooth_hsi(self):
        self.Hf = self.gaussian(self.H)
        self.Sf = self.gaussian(self.S)
        self.If = self.gaussian(self.I)

    def get_images(self):
        R = np.array(self.R)
        G = np.array(self.G)
        B = np.array(self.B)

        H = np.array(self.H)
        S = np.array(self.S)
        I = np.array(self.I)

        Rf = np.array(self.Rf)
        Gf = np.array(self.Gf)
        Bf = np.array(self.Bf)

        Hf = np.array(self.Hf)
        Sf = np.array(self.Sf)
        If = np.array(self.If)

        rgb = np.stack([R, G, B], axis=2)
        rgb_f = np.stack([Rf, Gf, Bf], axis=2)

        return R, G, B, H, S, I, Rf, Gf, Bf, Hf, Sf, If, rgb, rgb_f


path = "images/smoothening.jpeg"

obj = ColorSmoothing(path)

obj.rgb_to_hsi()
obj.smooth_rgb()
obj.smooth_hsi()

R, G, B, H, S, I, Rf, Gf, Bf, Hf, Sf, If, rgb, rgb_f = obj.get_images()

plt.figure(figsize=(14,10))

plt.subplot(4,4,1)
plt.imshow(rgb)
plt.title("RGB Original")
plt.axis('off')

plt.subplot(4,4,2)
plt.imshow(rgb_f)
plt.title("RGB Smoothed")
plt.axis('off')

plt.subplot(4,4,3)
plt.imshow(H, cmap='gray')
plt.title("H")
plt.axis('off')

plt.subplot(4,4,4)
plt.imshow(S, cmap='gray')
plt.title("S")
plt.axis('off')

plt.subplot(4,4,5)
plt.imshow(I, cmap='gray')
plt.title("I")
plt.axis('off')

plt.subplot(4,4,6)
plt.imshow(Hf, cmap='gray')
plt.title("Hf")
plt.axis('off')

plt.subplot(4,4,7)
plt.imshow(Sf, cmap='gray')
plt.title("Sf")
plt.axis('off')

plt.subplot(4,4,8)
plt.imshow(If, cmap='gray')
plt.title("If")
plt.axis('off')

plt.subplot(4,4,9)
plt.imshow(R, cmap='gray')
plt.title("R")
plt.axis('off')

plt.subplot(4,4,10)
plt.imshow(G, cmap='gray')
plt.title("G")
plt.axis('off')

plt.subplot(4,4,11)
plt.imshow(B, cmap='gray')
plt.title("B")
plt.axis('off')

plt.subplot(4,4,12)
plt.imshow(Rf, cmap='gray')
plt.title("Rf")
plt.axis('off')

plt.subplot(4,4,13)
plt.imshow(Gf, cmap='gray')
plt.title("Gf")
plt.axis('off')

plt.subplot(4,4,14)
plt.imshow(Bf, cmap='gray')
plt.title("Bf")
plt.axis('off')

plt.tight_layout()
plt.show()