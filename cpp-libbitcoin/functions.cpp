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
    // adding 300 so that some of the transactions would be unverified
    std::uniform_int_distribution<int> money(0, U[num].balance + 300);
    a.amount = money(mt);
    a.id = combine_hash_function(a.senderID+a.recipientID+std::to_string(a.amount));
    T.push_back(a);
    count++;
  }
}
//-------------------
void mining (block_chain &BC, std::vector<block> &B, std::vector<transaction> &exec_tr)
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> selectBlock(0, B.size() - 1);

  //checking if the block has been mined
  bool check = false;
  while(!check)
  {
    unsigned int i = selectBlock(mt);
    std::string zeros;
    std::string hash;
    std::string currentHash = B[i].merkleRootHash;
    if(BC.index() == 0)
    {
      B[i].prevBlockHash = '0';
    }
    else
    {
      B[i].prevBlockHash = BC.getLast().merkleRootHash;
    }
    char diff_target[B[i].difficultyTarget + 1];
    for (size_t j = 0; j != B[i].difficultyTarget; ++j)
    {
      diff_target[j] = '0';
    }
    diff_target[B[i].difficultyTarget] = '\0';
    zeros = diff_target;
    do
    {
      if (B[i].nonce > 100000)
      {
        break;
      }
      B[i].nonce++;
      std::stringstream combine;
      combine << B[i].nonce << B[i].prevBlockHash << B[i].timeStamp << currentHash << B[i].version << B[i].nonce;
      hash = combine_hash_function(combine.str());
      B[i].merkleRootHash = hash;
    } while(B[i].merkleRootHash.substr(0, B[i].difficultyTarget) != zeros);

    if (B[i].merkleRootHash.substr(0, B[i].difficultyTarget) == zeros)
    {
      check = true;
      exec_tr = B[i].getTransactions();
      BC.newBlock(B[i]);
      std::cout << "Block - > " << BC.index() << " Nonce - > " << B[i].nonce << "\n" << "Hash - > " << B[i].merkleRootHash << "\n\n";
    }
  }
}
