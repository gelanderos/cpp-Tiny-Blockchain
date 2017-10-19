#ifndef BLOCKHASH_H
#define BLOCKHASH_H
#include<string>

class block {
public:
  unsigned long index;
  unsigned long nonce;
  time_t timestamp;
  std::string blockdata;
  std::string hash;
  std::string previousblockhash;
};

std::string blockhasher(block btohash);
std::string hashtostring(unsigned char* phash);
block nextBlock(block lastblock);
block gsisblock();
unsigned long int proofofwork(block blocktosolve);

#endif
