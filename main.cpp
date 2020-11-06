#include "functions.h"
#include "functions.cpp"
#include "block.cpp"
#include "block_chain.cpp"

int main(){

  std::vector<user> U;
  std::vector<transaction> T;
  std::vector<transaction> count;
  generateUsers(U);
  generateTransactions(T, U);
  block_chain BC;

  std::random_device rd;
  std::mt19937 mt(rd());

  std::vector<block> list;
  while(T.size() >= 100)
  {
    std::vector<transaction> A;
    for (size_t i = 0; i != 100; ++i)
    {
      std::uniform_int_distribution<int> index(0, T.size() - 1);
      unsigned int a = index(mt);
      A.push_back(T[a]);
      count.push_back(T[a]);
      //instantly erasing so that the transaction could not repeat itself
      T.erase(T.begin() + a);
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
    std::cout << (*i).id << " " << (*i).amount << std::endl;
  }
  return 0;
}
