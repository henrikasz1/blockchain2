#include "functions.h"
#include "hash/functions.h"


//generating users (task 1)
void generateUsers(std::vector<user> &U)
{
  user a;
  //generate random number which will be the balance of a specific user
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> amount(100,1000000);

  for(size_t i = 0; i != U_NUM; ++i)
  {
    a.name = "user"+std::to_string(i);
    a.public_key = combine_hash_function(a.name);
    a.balance = amount(mt);
    U.push_back(a);
  }
}
//Generating transactions (task 2)
void generateTransactions(std::vector<transaction> &T, const std::vector<user> &U)
{
  unsigned int count = 0;
  unsigned int num;
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> amount(0,999);
  transaction a;
  for (size_t i = 0; i != T_NUM; ++i)
  {
    num = amount(mt);
    a.senderID = U[num].public_key;
    a.recipientID = U[amount(mt)].public_key;
    a.id = combine_hash_function(a.senderID+a.recipientID+std::to_string(count));
    std::uniform_int_distribution<int> money(0, U[num].balance);
    a.amount = money(mt);
    T.push_back(a);
    count++;
  }
}
