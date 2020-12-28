#include <iostream>
#include <assert.h>
#include "bloom_filter.h"

using namespace std;

bool TestBloomFilter() {
    printf("TestBloomFilter..\n");
    int n = 1000;
    double p = 0.01;
    BloomFilter bf(n,p);
    string tmp, key_tmp;
    for(int i=1;i<=n;i++) {
        tmp = to_string(i);
        key_tmp = tmp + tmp + tmp;
        bf.insertHash(key_tmp);
    }
    for(int i=1;i<=n;i++) {
        tmp = to_string(i);
        key_tmp = tmp + tmp + tmp;
        if(bf.matchHash(key_tmp) == false)
            cout<<key_tmp;
        assert(bf.matchHash(key_tmp));
    }
    printf("=== ok.\n");
    return true;
}

typedef bool (*TestUnitFun)();
TestUnitFun Tests[] = {
    TestBloomFilter,
};

int main() {
    int test_num = sizeof(Tests)/sizeof(TestUnitFun);
    int success_num = 0;
    for(int i=0; i<test_num; i++) {
        if(Tests[i]()) {
            success_num ++;
        }
    }
    printf("----------------------\n");
    printf("total  : %d\n", test_num);
    printf("success: %d\n", success_num);
    printf("fail   : %d\n", test_num - success_num);

    return 0;
}