import cv2
import numpy as np
import matplotlib.pyplot as plt

d0=30

class filters:

    def __init__(self,img):
        self.img=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
        self.r,self.g,self.b=cv2.split(self.img)

    def distance(self,u,v,cu,cv):
        return np.sqrt((u-cu)**2+(v-cv)**2)

    def freq_filter(self,plane,H):
        F=np.fft.fft2(plane)
        F=np.fft.fftshift(F)
        G=F*H
        g=np.fft.ifftshift(G)
        g=np.fft.ifft2(g)
        g=np.abs(g)
        return np.clip(g,0,255).astype(np.uint8)

    def build_ilpf(self,M,N,D0):
        H=np.zeros((M,N))
        cu=M//2
        cv=N//2
        for u in range(M):
            for v in range(N):
                if self.distance(u,v,cu,cv)<=D0:
                    H[u,v]=1
        return H

    def build_ihpf(self,M,N,D0):
        H=np.zeros((M,N))
        cu=M//2
        cv=N//2
        for u in range(M):
            for v in range(N):
                if self.distance(u,v,cu,cv)>D0:
                    H[u,v]=1
        return H

    def build_glpf(self,M,N,D0):
        H=np.zeros((M,N))
        cu=M//2
        cv=N//2
        for u in range(M):
            for v in range(N):
                D=self.distance(u,v,cu,cv)
                H[u,v]=np.exp(-(D**2)/(2*(D0**2)))
        return H

    def build_ghpf(self,M,N,D0):
        H=np.zeros((M,N))
        cu=M//2
        cv=N//2
        for u in range(M):
            for v in range(N):
                D=self.distance(u,v,cu,cv)
                H[u,v]=1-np.exp(-(D**2)/(2*(D0**2)))
        return H

    def apply(self,build_func,D0):
        M,N=self.r.shape
        H=build_func(M,N,D0)
        r=self.freq_filter(self.r,H)
        g=self.freq_filter(self.g,H)
        b=self.freq_filter(self.b,H)
        return np.dstack((r,g,b))

    def ideal_lowpass(self,D0):
        return self.apply(self.build_ilpf,D0)

    def ideal_highpass(self,D0):
        return self.apply(self.build_ihpf,D0)

    def gaussian_lowpass(self,D0):
        return self.apply(self.build_glpf,D0)

    def gaussian_highpass(self,D0):
        return self.apply(self.build_ghpf,D0)

img=cv2.imread("images/imgnoise.png")

if img is None:
    raise ValueError("Image path incorrect")

f=filters(img)

ilpf=f.ideal_lowpass(d0)
ihpf=f.ideal_highpass(d0)
glpf=f.gaussian_lowpass(d0)
ghpf=f.gaussian_highpass(d0)

plt.figure(figsize=(12,8))

plt.subplot(231)
plt.imshow(cv2.cvtColor(img,cv2.COLOR_BGR2RGB))
plt.title("Original")
plt.axis("off")

plt.subplot(232)
plt.imshow(ilpf)
plt.title("Ideal Low Pass")
plt.axis("off")

plt.subplot(233)
plt.imshow(ihpf)
plt.title("Ideal High Pass")
plt.axis("off")

plt.subplot(235)
plt.imshow(glpf)
plt.title("Gaussian Low Pass")
plt.axis("off")

plt.subplot(236)
plt.imshow(ghpf)
plt.title("Gaussian High Pass")
plt.axis("off")

plt.tight_layout()
plt.show()