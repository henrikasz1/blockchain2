// #include "user.h"
#include "functions.h"
#include "functions.cpp"

int main(){

  std::vector<user> U;
  generateUsers(U);
  for(std::vector<user>::iterator i = U.begin(); i != U.end(); ++i)
  {
    std::cout << (*i).name << " " << (*i).public_key << " " << (*i).balance << std::endl;
   }
  return 0;
}
