#RayTracer
#makefile for g++ linux

CC=g++
CFLAGS=-Wall


INCLUDE_PATH = -I./loadpng/ -I./Eigen/

SRC_DIR = .
VPATH = $(SRC_DIR)


SRC_FILES = $(foreach n, $(VPATH), $(wildcard $(n)/*.cpp))
SRC_FILES += ./loadpng/lodepng.cpp

OUTPUT_DIR = Release


all:
	$(CC) -O2 -o $(OUTPUT_DIR)/raytracer $(INCLUDE_PATH) $(INCLUDE_FILE) $(SRC_FILES)