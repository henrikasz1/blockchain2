#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <bitset>
#include <iterator>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include "functions.cpp"

// void readFile (std::string fileName, std::string &data);
void to_bin(std::string &input, std::vector<int> &bin);
std::string mixing_bin (std::vector<int> &bin);
void padding (std::vector<int> &bin);
std::string to_hex(std::vector<int> &bin);
std::string rand_str (const int length);
std::string combine_hash_function (std::string input);
void test1 (const int length);
void test2 ();

#endif// FUNCTIONS_H
