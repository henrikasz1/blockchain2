#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class transaction
{
  public:
    std::string id;
    std::string senderID;
    std::string recipientID;
    double amount;
};

#endif //TRANSACTION_H
