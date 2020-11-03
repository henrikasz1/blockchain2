// #include "user.h"
#include "functions.h"
#include "functions.cpp"

int main(){

  std::vector<user> U;
  std::vector<transaction> T;
  generateUsers(U);
  generateTransactions(T, U);
  return 0;
}
