#include <iostream>
#include <vector>
#include <openssl/sha.h>
#include <algorithm>
#include <string.h>
using namespace std;

void calSHA256(char* inp,char out_buff[65]){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, inp, strlen(inp));
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
      sprintf(out_buff + (i * 2), "%02x", hash[i]);
    }
    out_buff[64] = 0;
}

static void mergeCalSHA256(char* leftData,char* rightData,char out_buff[65]){

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256,leftData,strlen((const char*)leftData) );
    SHA256_Update(&sha256,rightData,strlen((const char*)rightData) );
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
      sprintf(out_buff + (i * 2), "%02x", hash[i]);
    }
    out_buff[64] = 0;
}


class MerkleTree{
public:
    vector<char*> tree;

    MerkleTree(){}
    MerkleTree(vector<char*> leaves){
      tree = InitMerkleTree(mergeCalSHA256,leaves);
    }

    size_t size(){return tree.size();}
    char* root(){return tree[0];}
    vector<char*> InitMerkleTree(void (*combineFn)(char*,char*,char*),vector<char*> leaves);

};

vector<char*> MerkleTree::InitMerkleTree(void (*combineFn)(char*,char*,char*),vector<char*> leaves){
    int nodeCount = leaves.size()*2 - 1;
    int delta = nodeCount - leaves.size();
    vector<char*> tree(nodeCount);//初始化结点
    cout<<"开始初始化Merkle Tree"<<endl;
    for(int i = 0 ;i<leaves.size();i++){
        tree[delta + i] = new char[65];
        memcpy(tree[delta + i],leaves[i],65);
        tree[delta + i][64] = 0;
    }

    int idx = nodeCount-1;
    while(idx > 0){
        int parent = (idx -1)/2;
        tree[parent] = new char[65];
        combineFn(tree[idx-1],tree[idx],tree[parent]);//相邻两个hash块串联，然后做hash运算
        tree[parent][64] = 0;
        idx-=2;
    }

    return tree;
  }

