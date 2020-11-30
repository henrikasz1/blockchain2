#ifndef BLOCK_CHAIN_H
#define BLOCK_CHAIN_H

#include <vector>
#include "block.h"

class block_chain
{
  public:
    void newBlock(const block &Block);
    int index() const;
    block getLast() const;
  private:
    std::vector<block> chain;
};

#endif //BLOCK_CHAIN_H
