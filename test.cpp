#include "MerkleTree.h"
#include <time.h>
using namespace std;

unsigned long GetTickCount()
{
    struct timespec ts;
 
    clock_gettime(CLOCK_MONOTONIC, &ts);
 
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

int main() {
    int test_num = 3000;
    string tmp;
    vector<string> data;
    for(int i = 1;i <= test_num;i++) {
        tmp = to_string(i);
        data.push_back(tmp);
    }
    MerkleTree tree = MerkleTree(data);
    int success_num = 0, failed_num = 0;
    cout<<"Test retrieve 1 to "<<test_num<<endl;
    
    unsigned long start_time = GetTickCount(); 
    for(int i = 0;i < test_num;i++) {
        if(tree.DataProof(data[i],false))
            success_num++;
        else
            failed_num++;
    }
    unsigned long end_time = GetTickCount(); 
    cout << "Success num: " << success_num << endl; 
    cout << "Failed num: " << failed_num << endl; 
    cout << "The run time is: " << (end_time - start_time) << "ms!" << endl; 

    cout<<"\nTest retrieve 1 to "<<test_num<<" with bloom filter"<<endl;
    success_num = 0;
    failed_num = 0;
    start_time = GetTickCount(); 
    for(int i = 0;i < test_num;i++) {
        if(tree.DataProof(data[i],true))
            success_num++;
        else
            failed_num++;
    }
    end_time = GetTickCount(); 
    cout << "Success num: " << success_num << endl; 
    cout << "Failed num: " << failed_num << endl; 
    cout << "The run time is: " << (end_time - start_time) << "ms!" << endl;     
    return 0;

}

