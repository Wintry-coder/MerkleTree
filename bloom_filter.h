#ifndef BLOOM_FILTER_H_
#define BLOOM_FILTER_H_

#include <string>
#include <vector>
#include <math.h>
using namespace std;

unsigned int RSHash(unsigned char *str, unsigned int len)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}

class BloomFilter {
public:
    BloomFilter(int n, double p);
    void insertHash(const string& hash_);
    bool matchHash(const string& hash_);
private:
    int num;
    int size; 
    string bitset;
};

BloomFilter::BloomFilter(int n, double p) {
    size = (int)ceil(-1 * (double)n * log(p) / pow(log(2), 2));
    num = (int)ceil(log(2) * (double)size / (double)(n));
    int bits = size;
    if (bits < 64) bits = 64;
    int bytes = (bits + 7) / 8; 
    bitset.resize(bytes);
   
}

void BloomFilter::insertHash(const string& hash_) {
    char* array = &bitset[0];
    uint32_t bits = bitset.size() * 8;
    uint32_t h = RSHash((unsigned char *)hash_.data(), hash_.size());
    const uint32_t delta = (h >> 17) | (h << 15); 
    for (size_t j = 0; j < num; j++) {
        const uint32_t bitpos = h % bits;
        array[bitpos / 8] |= (1 << (bitpos % 8));
        h += delta;
    }
}

bool BloomFilter::matchHash(const string& hash_) {
    int len = bitset.size();
    if (len < 2) return false;

    const char* array = bitset.data();
    const size_t bits = len * 8;

    uint32_t h = RSHash((unsigned char *)hash_.data(), hash_.size());
    const uint32_t delta = (h >> 17) | (h << 15);  
    for (size_t j = 0; j < num; j++) {
      const uint32_t bitpos = h % bits;
      if ((array[bitpos / 8] & (1 << (bitpos % 8))) == 0) return false;
      h += delta;
    }
    return true;
}

#endif