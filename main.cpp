#include <iostream>
#include <map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include "HuffmanTree.h"
#include "Compressor.h"
#include "Decompressor.h"
using namespace std;

int main() {
    //不能用>>读取文件，否则空格和回车就会丢失
    //读入包括回车与空格的字符，方法来自Stack Overflow
    string path;
    string op;
    cout<<"input 1 to compress a file, 2 to decompress\n";
    cin>>op;
    if(op=="1"){
        cout<<"Please enter the filename:\n";
        cin>>path;
        auto ysq=new Compressor(path);
        cout<<"Compression completes\n";
    }
    else{
        auto jyq=new Decompressor();
        cout<<"Decompression completes\n";
    }


    return 0;
}