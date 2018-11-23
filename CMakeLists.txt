cmake_minimum_required(VERSION 3.12)
project(third)

set(CMAKE_CXX_STANDARD 17)

add_executable(third main.cpp HuffmanTree.cpp HuffmanTree.h Compressor.cpp Compressor.h Decompressor.cpp Decompressor.h)