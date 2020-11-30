#include "hash/functions.h"
#include <string>
#include <vector>

std::string merkle_tree(std::vector<std::string> &A)
{
  while(A.size() > 1)
  {
    //making vector size to be even
    if (A.size() % 2 != 0)
    {
      A.push_back(A[A.size()]);
    }
    std::string hash;
    std::vector<std::string> B;
    for (std::vector<std::string>::iterator i = A.begin(); i != A.end(); i+=2)
    {
      hash = "";
      hash += (*i) + *(i + 1);
      B.push_back(combine_hash_function(hash));
    }
    A = B;
  }
  return A[0];
}
