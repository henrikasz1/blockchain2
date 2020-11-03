#include "functions.h"
#include "hash/functions.h"
// #include "functions.h"

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
