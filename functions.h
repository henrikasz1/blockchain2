#define pragma once

#include "transaction.h"
#include "user.h"
#include "block.h"
#include "block_chain.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <ctime>

#define U_NUM 1000
#define T_NUM 10000

//# more incoming
void generateUsers(std::vector<user> &U);
void generateTransactions(std::vector<transaction> &T, const std::vector<user> &U);
void mining (std::vector<block_chain> &BC, std::vector<block> &B);
