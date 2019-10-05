#!/usr/bin/env python3

from PIL import Image
import numpy as np
from glob import glob

MATRIX_W = 32
MATRIX_H = 32
ROTATION = 0#in degrees
MIRROR_X = False
MIRROR_Y = False
DISPLAY  = False

def convert_image(file_name, thres):
    image = Image.open(file_name)
    image = image.convert('L')#grey scale conversion
    image = image.rotate(ROTATION)
    image = image.resize((MATRIX_W,MATRIX_H))
    if MIRROR_X:
        image = image.transpose(Image.FLIP_LEFT_RIGHT)
    if MIRROR_Y:
        image = image.transpose(Image.FLIP_TOP_BOTTOM)
    image = np.array(image);#conversion to numpy array
    image = (255*(image > thres)).astype("uint8")#thresholding
    if DISPLAY:
        Image.fromarray(image, 'L').resize((640,640)).show()#display image
    result = []#binary conversion
    for i in range(MATRIX_H):
        for j in range(MATRIX_W):
            if j % 8 == 0:
                result.append(0)
            if image[i][j] != 0:
                result[-1] += 2**(j % 8)
    return result

def get_thres(file_name):
    return int(file_name.split("_")[-1].split(".")[0])

def get_duration(file_name):
    return int(file_name.split("_")[-2])

def write_frames(f, fh, to_write):
    size = 0
    f.write("const uint8_t internal_frames["+str(len(to_write))+"][128] = {\n")
    fh.write("extern const uint8_t internal_frames["+str(len(to_write))+"][128];\n")
    for i in range(len(to_write)):
        f.write("{")
        for j in range(len(to_write[i])):
            f.write(str(to_write[i][j]))
            size += 1
            if(j +1)!=len(to_write[i]):
                f.write(", ")
        f.write("}")
        if(i +1)!=len(to_write):
            f.write(",")
        f.write("\n")
    f.write("};\n")
    return size

def write_durations(f, fh, to_write):
    size = 0
    f.write("const uint8_t internal_frames_duration["+str(len(to_write))+"] = {")
    fh.write("extern const uint8_t internal_frames_duration["+str(len(to_write))+"];\n")
    for i in range(len(to_write)):
        f.write(str(to_write[i]))
        size += 1
        if(i +1)!=len(to_write):
            f.write(", ")
    f.write("};\n")
    return size



global_result = []
durations = []
files = glob('images/*.jpg')+glob('images/*.png')#add more formats if desired
files.sort()#alphabetical order

for image_file in files:
    result = convert_image(image_file, get_thres(image_file))
    durations.append(get_duration(image_file))
    global_result.append(result)

total_size = 0
f = open("frames_definition.c", "w+")
fh = open("frames_definition.h", "w+")

f.write('#include "frames_definition.h"\n\n')
f.write("const int internal_n_frames = "+str(len(durations))+";\n")
total_size += 4
fh.write("#pragma once\n")
fh.write('#include <stdint.h>\n\n')
fh.write("extern const int internal_n_frames;\n")
total_size += write_frames(f, fh, global_result)
total_size += write_durations(f, fh, durations)
f.close()
fh.close()

print("total used size for image definition: "+str(total_size)+" Bytes")
