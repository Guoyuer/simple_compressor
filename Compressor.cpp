#include "Compressor.h"

Compressor::Compressor(string path) {
    this->path = path;
    read_file_to_memory(path);

    get_freq_map();

    tree = new HuffmanTree(char_freq_map);

    char_code_map = tree->get_char_code_map();
    str2code();//用了char_code_map
//  show_coding_table();
//    print_code();
    char outpath[] = "code.dat";
    leftout = WriteBit(code, outpath);//string to const char *
    savemap();
}

void Compressor::get_freq_map() {
    string temp;
    for (char ch:this->str) {
        if (char_freq_map.find(ch) != char_freq_map.end())//若存在则自增1
            char_freq_map[ch]++;
        else//若不存在则初始化为1
            char_freq_map[ch] = 1;
    }
}

void Compressor::show_coding_table() {
    cout << "coding table:(size: " << char_code_map.size() << ")\n";
    for (auto &kv:char_code_map) {
        cout << kv.first << '\t' << char_freq_map[kv.first] << '\t' << kv.second << '\n';
    }
}

void Compressor::str2code() {
    for (char ch:this->str) {
        code += char_code_map[ch];
    }
}

void Compressor::print_code() {
    cout << "code is:\n";
    cout << this->code << endl;
}

void Compressor::read_file_to_memory(string path) {
    //不能用>>读取文件，否则空格和回车就会丢失
    //读入包括回车与空格的字符，方法来自Stack Overflow
    fstream file(path, ios::in);
    stringstream buffer;
    buffer << file.rdbuf();
    this->str = buffer.str();
    //cout<<str<<'\n';
}

int Compressor::WriteBit(string code, string path)//该函数返回的是最后多取了几位
{
    fstream out(path, ios::binary | ios::out);
    int leftout = 0;//记录最后一个不完整的字节缺了几位。
    int current_bit = 0;
    char *bit_buffer = new char();
    *bit_buffer = 0;
    for (int i = 0; i < code.size(); i++) {
        if (code[i] == '1') {
            *bit_buffer |= (1 << current_bit);
        }

        current_bit++;
        if (current_bit == 8) {
            out.write(bit_buffer, 1);
            current_bit = 0;
            *bit_buffer = 0;
        } else//如果current_bit不等于8，因为是从高位往低位放的，所以可以直接写入
        {
            if (i == code.size() - 1) {//如果已经到了二进制串末尾
                out.write(bit_buffer, 1);
                leftout = 8 - current_bit;
            }

        }
    }
    //out.write("E",1);
    out.close();
    return leftout;
}

void Compressor::savemap() {
    fstream testmap("map", ios::out | ios::binary);
    testmap << path << "\r\n";
    testmap << leftout << "\r\n";
    for (auto kv:char_freq_map) {
        testmap << kv.first << '\t' << kv.second << "\r\n";
    }
}