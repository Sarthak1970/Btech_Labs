import cv2
import math
import numpy as np
import matplotlib.pyplot as plt

class CannyEdge:

    def __init__(self, path):
        self.img = cv2.imread(path)
        self.gray = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)

        self.rows, self.cols = self.gray.shape

        self.smooth = [[0]*self.cols for _ in range(self.rows)]
        self.gx = [[0]*self.cols for _ in range(self.rows)]
        self.gy = [[0]*self.cols for _ in range(self.rows)]
        self.mag = [[0]*self.cols for _ in range(self.rows)]
        self.edge = [[0]*self.cols for _ in range(self.rows)]

    def gaussian_blur(self):
        kernel = [
            [1,2,1],
            [2,4,2],
            [1,2,1]
        ]

        for i in range(1, self.rows-1):
            for j in range(1, self.cols-1):
                sum_val = 0
                for x in range(-1, 2):
                    for y in range(-1, 2):
                        sum_val += int(self.gray[i+x][j+y]) * kernel[x+1][y+1]

                self.smooth[i][j] = sum_val // 16

    def gradient(self):
        sobelX = [
            [-1,0,1],
            [-2,0,2],
            [-1,0,1]
        ]

        sobelY = [
            [-1,-2,-1],
            [0,0,0],
            [1,2,1]
        ]

        for i in range(1, self.rows-1):
            for j in range(1, self.cols-1):
                sumX = 0
                sumY = 0

                for x in range(-1, 2):
                    for y in range(-1, 2):
                        sumX += self.smooth[i+x][j+y] * sobelX[x+1][y+1]
                        sumY += self.smooth[i+x][j+y] * sobelY[x+1][y+1]

                self.gx[i][j] = sumX
                self.gy[i][j] = sumY

                self.mag[i][j] = int(math.sqrt(sumX*sumX + sumY*sumY))

    def threshold(self, low, high):
        for i in range(self.rows):
            for j in range(self.cols):
                if self.mag[i][j] >= high:
                    self.edge[i][j] = 255
                elif self.mag[i][j] >= low:
                    self.edge[i][j] = 100
                else:
                    self.edge[i][j] = 0

    def get_images(self):
        edge_img = np.array(self.edge, dtype='uint8')
        original_rgb = cv2.cvtColor(self.img, cv2.COLOR_BGR2RGB)
        return original_rgb, edge_img


path1 = "images/canny1/canny1.jpeg"
path2 = "images/canny1/canny2.jpeg"

obj1 = CannyEdge(path1)
obj2 = CannyEdge(path2)

obj1.gaussian_blur()
obj1.gradient()

obj2.gaussian_blur()
obj2.gradient()

low = 50
high = 120

obj1.threshold(low, high)
obj2.threshold(low, high)

orig1, edge1 = obj1.get_images()
orig2, edge2 = obj2.get_images()

plt.figure()

plt.subplot(2,2,1)
plt.imshow(orig1)
plt.title("Image 1 Original")
plt.axis('off')

plt.subplot(2,2,2)
plt.imshow(edge1, cmap='gray')
plt.title("Image 1 Edge")
plt.axis('off')

plt.subplot(2,2,3)
plt.imshow(orig2)
plt.title("Image 2 Original")
plt.axis('off')

plt.subplot(2,2,4)
plt.imshow(edge2, cmap='gray')
plt.title("Image 2 Edge")
plt.axis('off')

plt.show()
