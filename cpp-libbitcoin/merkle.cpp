#include "hash/functions.h"
#include <string>
#include <vector>
#include <bitcoin/bitcoin.hpp>

bc::hash_digest create_merkle(bc::hash_list& merkle)
{
  // Stop if hash list is empty or contains one element
  if(merkle.empty())
  {
    return bc::null_hash;
  }
  else if(merkle.size() == 1)
  {
    return merkle[0];
  }
  // While there is more than 1 hash in the list, keep looping...
  while(merkle.size()>1)
  {
    // If number of hashes is odd, duplicate last hash in the list.
    if(merkle.size()%2!=0)
    {
      merkle.push_back(merkle.back());
    }
    // List size is now even.
    assert(merkle.size()%2==0);

    // New hash list.
    bc::hash_list new_merkle;

    // Loop through hashes 2 at a time.
    for(auto it = merkle.begin(); it != merkle.end(); it +=2)
    {
      // Join both current hashes together (concatenate).
      bc::data_chunk concat_data(bc::hash_size *2);
      auto concat = bc::serializer<decltype(concat_data.begin())>(concat_data.begin());
      concat.write_hash(*it);
      concat.write_hash(*(it +1));

      // Hash both of the hashes.
      bc::hash_digest new_root = bc::bitcoin_hash(concat_data);

      // Add this to the new list.
      new_merkle.push_back(new_root);
    }

      // This is the new list.
      merkle = new_merkle;

      // DEBUG output -------------------------------------
      // std::cout <<"Current merkle hash list:"<< std::endl;
      //
      // for(const auto& hash: merkle)
      // std::cout <<"  "<< bc::encode_base16(hash)<< std::endl;

      //std::cout << std::endl;
      // --------------------------------------------------
  }
  // Finally we end up with a single item.
  return merkle[0];
}

//Blockchain V0.2 merkle tree

// std::string merkle_tree(std::vector<std::string> &A)
// {
//   while(A.size() > 1)
//   {
//     //making vector size to be even
//     if (A.size() % 2 != 0)
//     {
//       A.push_back(A[A.size()]);
//     }
//     std::string hash;
//     std::vector<std::string> B;
//     for (std::vector<std::string>::iterator i = A.begin(); i != A.end(); i+=2)
//     {
//       hash = "";
//       hash += (*i) + *(i + 1);
//       B.push_back(combine_hash_function(hash));
//     }
//     A = B;
//   }
//   return A[0];
// }
