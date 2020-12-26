#include "MerkleTree.h"

using namespace std;

int main() {
   int n = 0;
   cout << "Please input a positive number to initialize the number of data blocks: ";
   while(cin>>n){
      if(n <= 0)
         cout << "Wrong input, please input again！\nPlease input a positive number to initialize the number of data blocks: ";
      else
         break;
   }
   cout << "Please enter the data string for each data block:\n";
   vector<char[65]>buff(n);
   vector<char*>data(n);
   string s;
   getchar();
   for(int i = 1; i <= n; i++){
      cout<< i <<": ";
      getline(cin, s);
      // char *p=(char*)s.c_str();
      // calSHA256(p,buff[i-1]);
      // data[i-1] = buff[i-1];
      // cout<<"The SHA256 hash value corresponding to the data block: "<<buff[i-1]<<endl;
      string hashs = SHA256(s);
      cout<<"The SHA256 hash value corresponding to the data block: "<< hashs <<endl;

   }
   // MerkleTree mt = MerkleTree(data);
   // printf("root: %s\n",mt.root());
   int op = 0;
/*   while(1)
   {
      cout<<"Please choose option 0-5：\n";
      cout<<"1. Update data block 2. Insert data block 3. Delete data block 4. Retrieve data block 5. Print MerkleTree 0. Exit\n";
      cin>>op;
      int index = 0;
      if(op == 0)
         break;
      switch (op)
      {
      case 1:
         cout<<"Please input the index of data block you want to uodate: ";
         cin>>index;
         mt.UpdateMerkleTree(index);
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
         cout<<"Please input correctly!\n";
         break;
      }
      
   }*/
   return 0;
 
}

