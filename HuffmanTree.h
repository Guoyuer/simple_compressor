#ifndef THIRD_HUFFMANTREE_H
#define THIRD_HUFFMANTREE_H

#include <map>
#include <unordered_map>
#include <list>
using namespace std;
typedef struct Node{//哈夫曼树的节点
    Node *left,*right;
    int freq;//出现频率
    char ch;//叶子节点存放字符
    Node(Node * left=NULL,Node * right=NULL,char ch='x',int freq=0){
        this->left=left;
        this->right=right;
        this->ch=ch;
        this->freq=freq;
    }
}Node;

class HuffmanTree {
public:
    HuffmanTree(map<char,int> &freq_map);

    unordered_map<char,string> get_char_code_map();
    map<string,char> get_code_char_map();

private:
    Node* root;
    void build_tree(map<char,int> &freq_map,Node* &root);
    void preOrder(Node* root,unordered_map<char,string> & ccmap,string temp);

};


#endif //THIRD_HUFFMANTREE_H
