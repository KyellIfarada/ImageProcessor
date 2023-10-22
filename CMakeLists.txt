cmake_minimum_required(VERSION 3.24)
project(IfaradaProcessor C)

set(CMAKE_C_STANDARD 99)

add_executable( Image.h  BMPHandler.h BMPHandler.c Image.c IfaradaImageProcessor.c HeaderUsageSample.c)

