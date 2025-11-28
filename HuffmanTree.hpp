#pragma once
#include <map>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct HuffmanNode {
    unsigned char pixelValue;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(unsigned char val, int freq):pixelValue(val),frequency(freq),left(nullptr),right(nullptr){}
    HuffmanNode(HuffmanNode* l, HuffmanNode* r):pixelValue(0),frequency(l->frequency + r->frequency),left(l),right(r){}
};

class HuffmanTree{
private:
    // 比较函数，用于优先队列（小顶堆）
    struct CompareNode {
        bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2) {
            return n1->frequency > n2->frequency;
        }
    };
    HuffmanNode* root;

    void deleteTree(HuffmanNode* node) {
        if(!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    // 辅助函数：递归复制树
    HuffmanNode* copyTree(HuffmanNode* node) {
        if (!node) return nullptr;
        HuffmanNode* newNode = new HuffmanNode(node->pixelValue, node->frequency);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

public:
    HuffmanTree(const map<unsigned char, int>& freqTable){
        if(freqTable.empty()){
            root = nullptr;
            return;
        }
        priority_queue<HuffmanNode*,vector<HuffmanNode*>,CompareNode> pq;
        for(const auto& pair:freqTable){
            pq.push(new HuffmanNode(pair.first,pair.second));
        }
        while(pq.size()>1){
            HuffmanNode *left=pq.top();
            pq.pop();
            HuffmanNode *right=pq.top();
            pq.pop();
            pq.push(new HuffmanNode(left,right));
        }
        root=pq.top();
    }

    ~HuffmanTree(){
        deleteTree(root);
    }

    // 拷贝构造函数
    HuffmanTree(const HuffmanTree& other) {
        root = copyTree(other.root);
    }

    // 赋值运算符重载
    HuffmanTree& operator=(const HuffmanTree& other) {
        if (this != &other) {
            deleteTree(root); // 释放旧资源
            root = copyTree(other.root); // 复制新资源
        }
        return *this;
    }

    // 元数据（根节点）接口
    HuffmanNode *data(){
        return root;
    }
};

