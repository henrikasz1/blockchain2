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
//-------------------
void mining (block_chain &BC, std::vector<block> &B)
{
  std::string zeros;
  for (size_t i = 0; i != B.size(); ++i)
  {
    //Genesis block
    if (i == 0)
    {
      B[i].prevBlockHash = '0';
    }
    else
    {
      B[i].prevBlockHash = B[i - 1].currentHash;
    }
    char diff_target[B[i].difficultyTarget + 1];
    for (size_t j = 0; j != B[i].difficultyTarget; ++j)
    {
      diff_target[j] = '0';
    }
    diff_target[B[i].difficultyTarget] = '\0';
    zeros = diff_target;
    do{
      B[i].nonce++;
      B[i].currentHash = combine_hash_function(std::to_string(B[i].nonce) + B[i].prevBlockHash + std::to_string(B[i].timeStamp) + std::to_string(B[i].version) + std::to_string(B[i].nonce));
    }while(B[i].currentHash.substr(0, B[i].difficultyTarget) != zeros);
    BC.newBlock(B[i]);

    std::cout << "Block - > " << i << " Nonce - > " << B[i].nonce << "\n" << "Hash - > " << B[i].currentHash << "\n\n";
  }
}
