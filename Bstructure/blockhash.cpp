#include<iostream>
#include<iomanip>
#include<tomcrypt.h>
#include<string>
#include<sstream>
#include"Bstructure/blockhash.h"

/*hashing the blocks*/
std::string blockhasher(block btohash) {
  std::string predatatohash = std::to_string(btohash.index) + std::to_string(btohash.nonce) + std::to_string(btohash.timestamp) + btohash.blockdata + btohash.previousblockhash;
  const std::string& datatohash = predatatohash;
  unsigned char* hashResult = (unsigned char*)malloc(sha256_desc.hashsize);
  hash_state md;
  sha256_init(&md);
  sha256_process(&md, (const unsigned char*) datatohash.c_str(), datatohash.size());
  sha256_done(&md, hashResult);
  std::string hashreturn = hashtostring(hashResult);
  return hashreturn;
}

/*hashdigest*/
std::string hashtostring(unsigned char* phash) {
  std::stringstream bhash;
  for (int i=0;i<32;i++){
    bhash << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(phash[i]);
  }
  std::string Bhash;
  Bhash = bhash.str();
 return Bhash;
}

/*genesis block data*/
block gsisblock(){
  block genesis;
  genesis.index=0;
  genesis.nonce=0;
  genesis.timestamp= time(0);
  genesis.blockdata = "hereby the blockchain begins";
  genesis.previousblockhash = "8b706cfa194b210233111d9f407067f81d81d6f4bf9374e369c3b24b8e7feb00";
  genesis.hash = blockhasher(genesis);
  return genesis;
}

/*block generator*/
block nextBlock(block lastblock){
  block nextBlock;
  nextBlock.index = lastblock.index + 1;
  std::cout << "This is block No." << nextBlock.index << std::endl;
  nextBlock.timestamp = time(0);
  std::cout << "This blocks timestamp: " << nextBlock.timestamp << std::endl;
  nextBlock.blockdata = "Next block to hash is" + std::to_string(nextBlock.index);
  std::cout << "This info is gonna be hashed into next block: " << nextBlock.blockdata << std::endl;
  nextBlock.previousblockhash = lastblock.hash;
  std::cout << "Last Blocks Hash is : "<< nextBlock.previousblockhash << std::endl;
  nextBlock.nonce = proofofwork(nextBlock);
  std::cout << "Here we do a little bit of work to find the nonce required which for this block is: " << nextBlock.nonce << std::endl;
  nextBlock.hash = blockhasher(nextBlock);
  std::cout << "This block hash is: "<< nextBlock.hash <<std::endl;
  return nextBlock;
}

/*proofofwork function*/
unsigned long int proofofwork(block blocktosolve){
  unsigned long int nonce;
  std::string hash;
  blocktosolve.nonce = 1;
  hash = blockhasher(blocktosolve);
  for (int i=0;;i++){
    if( hash.substr(0,7)=="0000000"){
      std::cout<< hash<<std::endl;
      break;
    }
    blocktosolve.nonce = i;
    hash = blockhasher(blocktosolve);
    }
  return blocktosolve.nonce;
}
