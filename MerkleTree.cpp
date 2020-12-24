#include <iostream>
#include <vector>
#include <openssl/sha.h>
#include <algorithm>
#include <string.h>
#include "MerkleTree.h"
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
  out_buff[65] = 0;
}

int main() {
   int n = 0;
   cout << "请输入一个正数，用于初始化数据块的个数：";
   while(cin>>n){
      if(n <= 0)
         cout << "输入不正确，请重新输入！\n请输入一个正数，用于初始化数据块的个数：";
      else
         break;
   }
   cout << "请输入每个数据块的数据字符串：\n";
   vector<char[65]>data(n);
   vector<char[65]>buff(n);
   for(int i = 1; i <= n; i++){
      printf("第%d个：",i);
      cin>>data[i-1];
      calSHA256(data[i-1],buff[i-1]);
      cout<<"该数据块对应的SHA256哈希值为:"<<buff[i-1]<<endl;
   }

   return 0;
 
}