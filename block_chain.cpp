#include "block_chain.h"

void block_chain::newBlock(const block &Block)
{
  this->chain.push_back(Block);
}
block block_chain::getLast() const {
  return this->chain.back();
}
int block_chain::index() const {
  return this->chain.size();
}
