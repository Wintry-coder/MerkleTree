#include "MerkleTree.h"

using namespace std;

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
   vector<char[65]>buff(n);
   vector<char*>data(n);
   string s;
   for(int i = 1; i <= n; i++){
      printf("第%d个：",i);
      cin>>s;
      char *p=(char*)s.c_str();
      calSHA256(p,buff[i-1]);
      data[i-1] = buff[i-1];
      cout<<"该数据块对应的SHA256哈希值为:"<<buff[i-1]<<endl;
   }
   MerkleTree mt = MerkleTree(data);
   printf("root: %s\n",mt.root());
   int op = 0;
   while(1)
   {
      cout<<"请输入操作：\n";
      cout<<"1.更新数据块 2.插入数据块 3.删除数据块 4.检索数据块 5.打印MerkleTree 0.退出\n";
      cin>>op;
      if(op == 0)
         break;
      switch (op)
      {
      case 1:
         break;
      case 2:
         break;
      case 3:
         break;
      case 4:
         break; 
      case 5:
         break;    
      default:
         cout<<"请正确输入！";
         break;
      }
      
   }
   return 0;
 
}

