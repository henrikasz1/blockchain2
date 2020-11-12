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
    //std::string currentHash;
    std::string merkleRootHash;
    std::time_t timeStamp{};
    unsigned int version = 1;
    unsigned int difficultyTarget = 3;
    unsigned long int nonce = 0;

    block();
    void setTr(std::vector<transaction> &transactions);
    std::vector<transaction> getTransactions() const;
  private:
    //body of the block
    std::vector<transaction> transactions;
};

#endif //BLOCK_H
