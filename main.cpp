#include "functions.h"
#include "functions.cpp"
#include "block.cpp"
#include "block_chain.cpp"
#include "hash/functions.h"

int main(){
  std::cout << "Program started \n" << std::endl;
  std::vector<user> U;
  std::vector<transaction> T;
  std::vector<transaction> count;
  generateUsers(U);
  std::cout << "Users generated \n" << std::endl;
  generateTransactions(T, U);
  std::cout << "Transactions generated \n" << std::endl;
  block_chain BC;

  std::random_device rd;
  std::mt19937 mt(rd());

  std::vector<block> list;

  std::cout << "Verifying transactions \n" << std::endl;
  unsigned int verificationsFailed = 0;
  //std::vector<transaction> verified_T;
  for (std::vector<transaction>::iterator i = T.begin(); i != T.end(); ++i)
  {
    //verifying transactions (checking if balance is sufficient)
    for (std::vector<user>::iterator j = U.begin(); j != U.end(); ++j)
    {
      unsigned int c = 0;
      if (((*i).senderID == (*j).public_key && (*i).amount > (*j).balance))
      {
        T.erase(i);
        verificationsFailed++;
      }
    }
    if ((*i).id != combine_hash_function((*i).senderID + (*i).recipientID + std::to_string((*i).amount)))
    {
      T.erase(i);
      verificationsFailed++;
    }
  }
  std::cout << verificationsFailed << " transactions unverified \n" << std::endl;

  while (T.size())
  {
    std::vector<transaction> A;
    if (T.size() >= 100)
    {
      for (size_t i = 0; i != 100; ++i)
      {
        std::uniform_int_distribution<int> index(0, T.size() - 1);
        unsigned int a = index(mt);
        A.push_back(T[a]);
        count.push_back(T[a]);
        //instantly erasing so that the transaction could not repeat itself
        T.erase(T.begin() + a);
      }
    }
    else
    {
      for (size_t i = 0; i != T.size(); ++i)
      {
        A.push_back(T[i]);
        count.push_back(T[i]);
      }
      T.clear();
    }
    block B;
    B.setTr(A);
    list.push_back(B);
  }

  mining(BC, list);
  for (std::vector<transaction>::iterator i = count.begin(); i != count.end(); ++i)
  {
    for (std::vector<user>::iterator j = U.begin(); j != U.end(); ++j)
    {
      if ((*i).senderID == (*j).public_key)
      {
        (*j).balance -= (*i).amount;
      }
    }
  }
  return 0;
}
