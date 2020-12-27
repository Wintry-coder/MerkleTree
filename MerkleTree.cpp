#include "MerkleTree.h"
unsigned char* filter;
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
   filter = malloc(FILTER_SIZE_BYTES);
   vector<string> data;
   string s;
   getchar();
   for(int i = 1; i <= n; i++){
      cout<< i <<": ";
      getline(cin, s);
      data.push_back(s);
   }
   MerkleTree tree = MerkleTree(data);
   cout<<"Init Merkle Tree successfully!"<<endl;   
   int op = 0;
   while(1)
   {
      cout<<"Please choose option 0-5：\n";
      cout<<"1. Update data block 2. Insert data block 3. Delete data block 4. Retrieve data block 0. Exit\n";
      cin>>op;
      int index = 0;
      string ssd;
      bool enable_bf = false;
      if(op == 0)
         break;
      switch (op)
      {
      case 1:
         cout<<"Please input the index of data block you want to update( index starts from 1 ): ";
         cin>>index;
         getchar();
         cout << "Please enter the data string for the data block:\n";
         getline(cin, s);
         tree.UpdateMerkleTree(index,s);
         break;
      case 2:
         cout<<"Please input a positive number to represent the number of data blocks you want to insert: ";
         while(cin>>n){
            if(n <= 0)
               cout << "Wrong input, please input again！\nPlease input a positive number to initialize the number of data blocks: ";
            else
               break;
         }
         getchar();
         cout << "Please enter the data string for each data block:\n";
         for(int i = 1; i <= n; i++){
            cout<< i <<": ";
            getline(cin, s);
            data.push_back(s);
         }         
         tree = MerkleTree(data);
         break;
      case 3:
         cout << "Please enter the data string you want delete:\n";
         getchar();
         getline(cin, ssd);
         for(auto iter = data.begin();iter!=data.end();iter++){
            if(*iter == ssd){
               iter = data.erase(iter);
               iter--;
            }
         }
         tree = MerkleTree(data);
         break;
      case 4:
         cout << "Please choose whether to use bloom filter(y or n): ";
         cin>>ssd;
         if(ssd == "y")
         {
            enable_bf = true;
            cout<<"Bloom Filter start!\n";
         }
         getchar();
         cout << "Please enter the data string you want retrieve:\n";
         getline(cin, ssd);
         if(tree.DataProof(ssd,enable_bf))
            cout<<"Success!\n";
         else
            cout<<"Failed!\n";
         break; 
      default:
         cout<<"Please input correctly!\n";
         break;
      }
      
   }
   free(filter);
   return 0;
}

