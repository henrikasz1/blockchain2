#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <ctime>
#include "transaction.h"

class block
{
  public:
    //header
    std::string prevBlockHash;
    std::string currentHash;
    std::time_t timeStamp{};
    unsigned int version = 1;
    unsigned int difficultyTarget = 3;
    unsigned long int nonce = 0;

    block();
    void setTr(const std::vector<transaction> &transactions);
  private:
    //body of the block
    std::vector<transaction> transactions;
};

#endif //BLOCK_H
