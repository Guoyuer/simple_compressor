#include "Decompressor.h"

Decompressor::Decompressor() {
    read_map();//get code freq map;
    char codepath[] = "code.dat";
    HT = new HuffmanTree(char_freq_map);
    code_char_map = HT->get_code_char_map();
    ReadBit(codepath, leftout);
    code2str();
    //cout<<code<<'\n';
//    show_coding_table();
    writeback();
}

void Decompressor::read_map() {
    fstream dict("map", ios::in | ios::binary);
    char *buf = new char();
    string temp;
    //第一行，读取压缩前的文件名
    dict.getline(buf, 20);
    temp = string(buf);
    //cout<<temp<<'\n';
    rawname = temp;
    //第二行，读取最后一字节缺了几位
    dict.getline(buf, 20);
    temp = string(buf);
    leftout = atoi(temp.c_str());
    int line = 3;
    while (!dict.eof()) {

        dict.getline(buf, 20);
        temp = string(buf);
        if (temp.size() == 0) {//遇到了换行符
            dict.getline(buf, 20);
            if (dict.eof())
                break;//如果是最后一行，则退出读取；
            temp = string(buf);
            string tempv = temp.substr(1);//跳过'\t'
            int v = atoi(tempv.c_str());
            char_freq_map['\n'] = v;
            continue;
        }
        char k = temp[0];
        string tempv = temp.substr(2);
        int v = atoi(tempv.c_str());
        //cout<<k<<'\t'<<v<<"\r\n";
        char_freq_map[temp[0]] = v;
        line++;
    }
}

void Decompressor::ReadBit(char path[], int leftout) {
    FILE *in;
    in = fopen(path, "rb");
    char c;
    while (!feof(in)) {
        c = fgetc(in);
        for (int i = 0; i < 8; i++) {
            code += (char) ((c & 1) + 48);
            c >>= 1;
        }
    }
    fclose(in);
    code.resize(code.size() - leftout - 8);
}

void Decompressor::code2str() {
    string temp;
    for (char ch:code) {
        temp += ch;
        map<string, char>::iterator it;
        if ((it = code_char_map.find(temp)) != code_char_map.end()) {
            text += it->second;
            temp.clear();
        }
    }
}

void Decompressor::show_coding_table() {
    cout << "coding table:(size: " << code_char_map.size() << ")\n";
    for (auto &kv:code_char_map) {
        cout << kv.second << '\t' << char_freq_map[kv.second] << '\t' << kv.first << '\n';
    }

}

void Decompressor::writeback() {
    rawname.pop_back();//去除最后的r
    fstream out(rawname, ios::out);
    if (out.fail()) {
        cout << "write fail!\n";
        return;
    }
    out << text;
    out.close();
}
