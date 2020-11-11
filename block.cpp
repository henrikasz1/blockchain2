#include "block.h"
#include "merkle.cpp"

block::block()
{
  timeStamp = time(nullptr);
}
void block::setTr(std::vector<transaction> &transactions)
{
  this->transactions = transactions;
  //referencing to the merkle tree
  std::vector<std::string> transactions_id;
  for (std::vector<transaction>::iterator i = transactions.begin(); i != transactions.end(); ++i)
  {
    transactions_id.push_back((*i).id);
  }
  merkleRootHash = merkle_tree(transactions_id);
}
