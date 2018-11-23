#ifndef THIRD_DECOMPRESSOR_H
#define THIRD_DECOMPRESSOR_H

#include "HuffmanTree.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

class Decompressor {
public:
    Decompressor();

    void show_coding_table();

private:
    void read_map();

    void ReadBit(char path[], int leftout);

    void code2str();

    void writeback();

    map<string, char> code_char_map;
    map<char, int> char_freq_map;
    int leftout;
    string code;
    string text;
    string rawname;
    HuffmanTree *HT;
};


#endif //THIRD_DECOMPRESSOR_H
