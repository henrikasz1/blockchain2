#include "functions.h"
#include "functions.cpp"
#include "block.cpp"
#include "block_chain.cpp"
#include "hash/functions.h"

int main()
{
  std::cout << "Program started \n" << std::endl;
  std::vector<user> U;
  std::vector<transaction> T;
  generateUsers(U);
  std::cout << "Users generated \n" << std::endl;
  generateTransactions(T, U);
  std::cout << "Transactions generated \n" << std::endl;
  block_chain BC;

  std::random_device rd;
  std::mt19937 mt(rd());

  std::vector<block> list;
  std::vector<int> K;

  std::cout << "Verifying transactions \n" << std::endl;
  unsigned int verificationsFailed = 0;

  for (size_t i = 0; i != T.size(); ++i)
  {
    //verifying transactions (checking if balance is sufficient)
    for (std::vector<user>::iterator j = U.begin(); j != U.end(); ++j)
    {
      if (T[i].senderID == (*j).public_key && T[i].amount > (*j).balance)
      {
        verificationsFailed++;
      }
    }
    if (T[i].id != combine_hash_function(T[i].senderID + T[i].recipientID + std::to_string(T[i].amount)))
    {
      verificationsFailed++;
    }
  }
  for (size_t i = 0; i != K.size(); ++i)
  {
    T.erase(T.begin() + K[i]);
  }

  std::cout << verificationsFailed << " transactions unverified \n" << std::endl;
  std::vector<transaction> tr_copy;
  
  while (T.size())
  {
    tr_copy = T;
    std::vector<transaction> exec_tr;
    std::vector<transaction> A;
    if (T.size() >= 100)
    {
      for (size_t i = 0; i != 100; ++i)
      {
        std::uniform_int_distribution<int> index(0, tr_copy.size() - 1);
        unsigned int a = index(mt);
        A.push_back(tr_copy[a]);
        //instantly erasing so that the transaction could not repeat itself
        tr_copy.erase(tr_copy.begin() + a);
      }
    }
    else
    {
      for (size_t i = 0; i != T.size(); ++i)
      {
        A.push_back(T[i]);
      }
    }
    block B;
    B.setTr(A);
    list.push_back(B);
    if (list.size() == 5)
    {
      mining(BC, list, exec_tr);
      K.clear();
      for (size_t i = 0; i != T.size(); ++i)
      {
        for (std::vector<transaction>::iterator j = exec_tr.begin(); j != exec_tr.end(); j++)
        {
          if (T[i].id == (*j).id)
          {
            K.push_back(i);
          }
        }
      }
      for (size_t i = 0; i != K.size(); ++i)
      {
        T.erase(T.begin() + K[i]);
      }
      //------
      for (std::vector<transaction>::iterator i = exec_tr.begin(); i != exec_tr.end(); ++i)
      {
        for (std::vector<user>::iterator j = U.begin(); j != U.end(); ++j)
        {
          if ((*i).senderID == (*j).public_key)
          {
            (*j).balance -= (*i).amount;
          }
          else if ((*i).recipientID == (*j).public_key)
          {
            (*j).balance += (*i).amount;
          }
        }
      }
      //-----
      list.clear();
      exec_tr.clear();
    }
  }
  return 0;
}
