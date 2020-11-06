#include "block.h"

block::block()
{
  timeStamp = time(nullptr);
}
void block::setTr(const std::vector<transaction> &transactions)
{
  this->transactions = transactions;
}
