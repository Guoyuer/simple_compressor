#include "HuffmanTree.h"

class cmp {//cmp for sort
public:
    bool operator()(Node*& t1, Node*& t2) {
        return t1->freq < t2->freq;
    }
};
HuffmanTree::HuffmanTree(map<char,int> &freq_map) {
    build_tree(freq_map,root);
}
void HuffmanTree::build_tree(map<char,int> &freq_map,Node* &root){
    list<Node*> forest;
    Node *temproot;
    Node *left,*right;//左右两棵子树
    for(auto& kv:freq_map){
        temproot=new Node(NULL,NULL,kv.first,kv.second);
        forest.push_back(temproot);
    }
    forest.sort(cmp());//初始排序，降低后续时间复杂度
    while(forest.size()>=2){
        left=forest.front();
        forest.pop_front();
        right=forest.front();
        forest.pop_front();
        temproot=new Node(left,right,'\0',left->freq+right->freq);
        auto it=forest.begin();
        for(it=forest.begin();it!=forest.end();++it){//注意.end()返回的迭代器一般指向线性元素的后一个元素
            Node* flag=*it;//flag为游标
            if(temproot->freq <= flag->freq){//插入在第一个freq比后面的元素大的元素之前
                forest.insert(it,temproot);
                break;
            }//1 2 3 3 4 5
        }
        if(it==forest.end())
            forest.push_back(temproot);//没有找到比它大的元素，但是也必须插入
    }
    root=forest.front();//当只有一个不同字符，不会进入循环；成立；当有多个不同字符，会进入循环，但是最终会因为合并而减为一个，成立。

}


void HuffmanTree::preOrder(Node* root,unordered_map<char,string> & ccmap,string temp){
    if(root){
        if(!root->left&&!root->right){//如果是叶子
            ccmap[root->ch]=temp;
        }
        if(root->left) preOrder(root->left,ccmap,temp+"0");
        if(root->right) preOrder(root->right,ccmap,temp+"1");
    }
};
unordered_map<char,string> HuffmanTree::get_char_code_map(){
    unordered_map<char,string> char_code_map;
    string temp;
    preOrder(root,char_code_map,temp);
    return char_code_map;
};
map<string,char> HuffmanTree::get_code_char_map(){
    map<string,char> code_char_map;
    unordered_map<char,string> char_code_map;
    char_code_map=this->get_char_code_map();
    for(auto& kv:char_code_map){
            code_char_map[kv.second]=kv.first;
        }
    return code_char_map;
};