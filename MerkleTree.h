#ifndef MERKLE_TREE_H_
#define MERKLE_TREE_H_

#include <iostream>
#include <vector>
#include <openssl/sha.h>
#include <algorithm>
#include <assert.h>
#include <string.h>
#include "bloom_filter.h"
using namespace std;

#define miss_rate 0.01

string SHA256(string data) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data.data(), data.size());
  SHA256_Final(hash, &sha256);
  return string((char*)hash);
}
struct MerkleTree;
struct DataHashNode{
    DataHashNode *left;
    DataHashNode *right;
    DataHashNode *parent;
    MerkleTree *tree;
    string hash_;
    int left_index;
    int right_index;
    BloomFilter *bf;
    
    DataHashNode(string str, MerkleTree* tree, int i):left(nullptr),right(nullptr),parent(nullptr),left_index(i),right_index(i),
    hash_(str),bf(nullptr),tree(tree){}

    DataHashNode(DataHashNode* _left,DataHashNode* _right,DataHashNode* _parent,string _hash,MerkleTree* tree):left(_left),
    right(_right),parent(_parent),hash_(_hash),tree(tree),left_index(left->left_index){
        right_index = right == nullptr?left->right_index:right->right_index;
        createBF();
    }
    DataHashNode* findBF(string hashstr);
    void createBF();
};

struct MerkleTree{
    DataHashNode* root;
    vector<DataHashNode*> leaves;

    MerkleTree(){}
    MerkleTree(vector<string> data){
        DataHashNode* leaf;
        for(int i = 0; i < data.size(); i++) {
            leaf = new DataHashNode(SHA256(data[i]),this,i);
            leaves.push_back(leaf);
        }
        // 叶子节点奇数个，复制最后一个节点
        if(data.size()%2 == 1) {
            leaf = new DataHashNode(SHA256(data[data.size()-1]),this,data.size());
            leaves.push_back(leaf);
        }
        root = InitMerkleTree(leaves);
        
    }
    DataHashNode* InitMerkleTree(vector<DataHashNode*> &nodes);
    bool DataProof(string data, int enable_bloom_filter);
    DataHashNode* findLeaf(string str);
    void UpdateMerkleTree(int index, string str);

};
DataHashNode* MerkleTree::InitMerkleTree(vector<DataHashNode*> &nodes){
    if(nodes.size() == 1) 
        return nodes[0];
    vector<DataHashNode*> temp;
    DataHashNode* tmp, *left, *right;

    string hash_tmp;
    for(int i = 0; i < nodes.size(); i += 2) {
        left = nodes[i];
        if(i+1 == nodes.size()) {
            tmp = new DataHashNode(left, nullptr, nullptr, left->hash_, this);
            temp.push_back(tmp);
            left->parent = tmp;// 内部节点奇数个，只对left节点进行计算
        }
        else {
            right = nodes[i+1];
            string temp_hash = left->hash_ + right->hash_;
            hash_tmp = SHA256(temp_hash);
            tmp = new DataHashNode(left, right, nullptr, hash_tmp, this);
            temp.push_back(tmp);
            left->parent = tmp;
            right->parent = tmp;
        }
    }
    return InitMerkleTree(temp);
}

bool MerkleTree::DataProof(string data, int enable_bloom_filter){
    string hashstr = SHA256(data);
    DataHashNode* leaf;
    if(enable_bloom_filter){
        leaf = root->findBF(hashstr);
    }else{
        leaf = findLeaf(hashstr);
    }
    if(leaf == nullptr)
        return false;
    DataHashNode* current_parent = leaf->parent;
    string root_hash = leaf->hash_;
    string combo_hash;
    while(current_parent != nullptr) {
        if(current_parent->left == leaf) {
            if(current_parent->right){
                combo_hash = root_hash + current_parent->right->hash_;
                root_hash = SHA256(combo_hash);
            }
        }
        else {
            combo_hash = current_parent->left->hash_ + root_hash;
            root_hash = SHA256(combo_hash);
        }
        leaf = current_parent;
        current_parent = current_parent->parent;
    }
    if(root_hash == root->hash_) 
        return true;
    return false;    
}


DataHashNode* MerkleTree::findLeaf(string str) {
    for(int i = 0; i< leaves.size(); i++) {
        if(str == leaves[i]->hash_) {
            return leaves[i];
        }
    }
    return nullptr;
}


void MerkleTree::UpdateMerkleTree(int index, string str){
    string hash_ = SHA256(str);
    if(index > leaves.size()||index <= 0){
        cout<<"Wrong index\n";
        return;
    }
    DataHashNode* leaf = leaves[index-1];
    leaf->hash_ = hash_;
    DataHashNode* current_parent = leaf->parent;
    string combo_hash;
    while(current_parent != nullptr) {
        if(current_parent->left == leaf) {
            if(current_parent->right){
                combo_hash = hash_ + current_parent->right->hash_;
                hash_ = SHA256(combo_hash);
            }
        }
        else {
            combo_hash = current_parent->left->hash_ + hash_;
            hash_ = SHA256(combo_hash);
        }
        current_parent->hash_ = hash_;
        leaf = current_parent;
        current_parent = current_parent->parent;
    }    
}

void DataHashNode::createBF(){
    int n = right_index - left_index+ 1;
    bf = new BloomFilter(n, miss_rate);
    for(int i=left_index; i<=right_index; i++) {
        bf->insertHash(((tree->leaves)[i])->hash_);
    }    
}

DataHashNode* DataHashNode::findBF(string hashstr){
    if(left == nullptr && right == nullptr) {  
        if(hashstr == (tree->leaves)[left_index]->hash_) {
            return (tree->leaves)[left_index];
        }
        return nullptr;
    }
    else { 
        if(!bf->matchHash(hashstr))
            return nullptr;
        else { 
            DataHashNode* left_ = left->findBF(hashstr);
            DataHashNode* right_ = right == nullptr?nullptr:right->findBF(hashstr);
            if(left_)
                return left_;
            else 
                return right_;
        }
    }    
}
#endif
