#include "block_chain.h"

void block_chain::newBlock(const block &Block)
{
  this->chain.push_back(Block);
}
