#!/usr/bin/env python3

from PIL import Image
import numpy as np
from glob import glob

MATRIX_W = 32
MATRIX_H = 32

def swap_endian(number):#TODO manage endianness
    return number

def convert_image(file_name, thres):#TODO add rotation and miror options
    image = Image.open(file_name)
    image = image.convert('L')#grey scale conversion
    image = image.resize((MATRIX_W,MATRIX_H))
    image = np.array(image);#conversion to numpy array
    image = (255*(image > thres)).astype("uint8")#thresholding
    Image.fromarray(image, 'L').resize((640,640)).show()#display image

    result = []
    for i in range(MATRIX_H):
        result.append(0)
        for j in range(MATRIX_W):
            if image[i][j] != 0:
                result[i] += 2**j
    return result

def get_thres(file_name):
    return int(file_name.split("_")[-1].split(".")[0])

def get_duration(file_name):
    return int(file_name.split("_")[-2])

def write_frames(f, fh, to_write):
    f.write("const uint_32 internal_frames["+str(len(to_write))+"][32] = {\n")
    fh.write("extern const uint_32 internal_frames["+str(len(to_write))+"][32];\n")
    for i in range(len(to_write)):
        f.write("{")
        for j in range(len(to_write[i])):
            f.write(str(swap_endian(to_write[i][j])))
            if(j +1)!=len(to_write[i]):
                f.write(", ")
        f.write("}")
        if(i +1)!=len(to_write):
            f.write(",")
        f.write("\n")
    f.write("};\n")

def write_durations(f, fh, to_write):
    f.write("const uint_8 internal_frames_duration["+str(len(to_write))+"] = {")
    fh.write("extern const uint_8 internal_frames_duration["+str(len(to_write))+"];\n")
    for i in range(len(to_write)):
        f.write(str(to_write[i]))
        if(i +1)!=len(to_write):
            f.write(", ")
    f.write("};\n")


global_result = []
durations = []
files = glob('images/*.jpg')+glob('images/*.png')#add more formats if desired
files.sort()#alphabetical order

for image_file in files:
    result = convert_image(image_file, get_thres(image_file))
    durations.append(get_duration(image_file))
    global_result.append(result)



f = open("../frames_definition.c", "w+")
fh = open("../frames_definition.h", "w+")

f.write("const int internal_n_frames = "+str(len(durations))+";\n")
fh.write("#pragma once\n")
fh.write("extern const int internal_n_frames;\n")
write_frames(f, fh, global_result)
write_durations(f, fh, durations)
f.close()
fh.close()
#TODO add memory use
