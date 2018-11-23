#ifndef THIRD_COMPRESSOR_H
#define THIRD_COMPRESSOR_H

#include "HuffmanTree.h"
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <stdlib.h>
using namespace std;
class Compressor {
public:
    explicit Compressor(string path);
    void show_coding_table();

    int leftout;
private:
    string path;
    map<char,int> char_freq_map;//from
    unordered_map <char,string> char_code_map;//to
    string str;//原文
    string code;//压缩码

    HuffmanTree *tree;//保存哈夫曼树
    void str2code();
    void read_file_to_memory(string path);
    void print_code();
    int WriteBit(string code,string path);
    void savemap();
    void get_freq_map();


};


#endif //THIRD_COMPRESSOR_H
