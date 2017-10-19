#include<iostream>
#include<ctime>
#include"Bstructure/blockhash.h"

int main(){
  block blockchain[100];
  blockchain[0] = gsisblock();
  for (int i=1;i<100;i++){
    blockchain[i] = nextBlock(blockchain[i-1]);
  }
  return 0;
}
