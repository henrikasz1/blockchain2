#include "block.h"
#include "merkle.cpp"
#include <stdio.h>
#include <string.h>
#include <bitcoin/bitcoin.hpp>

block::block()
{
  timeStamp = time(nullptr);
}
void block::setTr(std::vector<transaction> &transactions)
{
  this->transactions = transactions;
  //referencing to the merkle tree
  std::vector<std::string> transactions_id;
  bc::hash_list hashes {};

  for (std::vector<transaction>::iterator i = transactions.begin(); i != transactions.end(); ++i)
  {
    //converting string into char because of the format bd::hash_literal requires
    char t_id[65];

    strcpy(t_id, (*i).id.c_str());

    transactions_id.push_back((*i).id);
    hashes.push_back(bc::hash_literal(t_id));
  }
  //bc::hash_list hashes = transactions_id;
  //merkleRootHash = merkle_tree(transactions_id);
  //merkleRootHash = create_merkle(hashes);
  //bc::hash_digest merkle_root = create_merkle(hashes);
  merkleRootHash = bc::encode_base16(create_merkle(hashes));
}
std::vector<transaction> block::getTransactions() const
{
  return this->transactions;
}
