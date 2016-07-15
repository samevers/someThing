#!/usr/bin/python
from scipy.misc import imread, imshow
img = imread("cat.jpg")
print img.shape
for i in range(0,len(img)):
	print img[i]
#    for j in range(0,len(img[i])):
#        print img[i][j]
