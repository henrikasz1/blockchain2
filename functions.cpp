#include "functions.h"

// void readFile (std::string fileName, std::string &data)//reading file into one string
// {
//   std::ifstream in (fileName);
//   std::stringstream a;
//   a << in.rdbuf();
//   data = a.str();
//   in.close();
// }
//-----
void to_bin(std::string &input, std::vector<int> &bin)//converting text into binary system
{
    std::string binary;
    for(char a : input)
    {
      binary = std::bitset<8>(int(a)).to_string();
      for (char b : binary)
      {
        bin.push_back(int(b) - 48);
      }
    }
}
//-----
std::string mixing_bin (std::vector<int> &bin)//mixing values so that the output would be irrecoverable
{
  for(size_t i = 0; i != bin.size() - 4; ++i)
  {
    if (i % 2 == 0)
    {
      bin[i] = bin[i + 4] ^= bin[i]; //using XOR logic operator
      bin[i +4] = bin[bin.size() - 1] ^= bin[i];
    }
    else
    {
      bin[i + 2] = bin[i] ^= bin[i + 2]; //using XOR logic operator
    }
  }
  for(int i = 0; i < bin.size() / 2; i++) {
        bin[i] = bin[i] ^= bin[bin.size() / 2 + i];
        bin[bin.size() - i - 1] = bin[i] ^= bin[bin.size() - i - 1];
        bin[bin.size() / 2  - i] = bin[i] ^= bin[bin.size() / 2 + 1];
    }
  while(bin.size() != 256)//altering vector's size to 256 after going through all logic gates
  {
    bin.pop_back();
  }

  std::stringstream ss;
  std::copy(bin.begin(), bin.end(), std::ostream_iterator<int>(ss, ""));//https://stackoverflow.com/questions/2518979/how-to-transform-a-vectorint-into-a-string/2519011

  return ss.str();
}
//-----
void padding (std::vector<int> &bin)
{
  if (bin.size() < 256)
  {
    std::string size = std::bitset<8>(bin.size()).to_string();
    std::vector<int> binsz;
    for (size_t i = 0; i != size.length(); ++i)
    {
      binsz.push_back(int(size[i]) - 48);
    }
    unsigned int a = 0;
    std::vector<int> pad;
    for (size_t i = 0; i != 256 - bin.size(); i += 8)
    {
      if (a < bin.size())
      {
        for (size_t j = 0; j != binsz.size(); ++j)
        {
          pad.push_back(binsz[j] ^= bin[a]);
          a++;
        }
      }
      else
      {
        for (size_t j = 0; j != binsz.size(); ++j)
        {
          pad.push_back(binsz[j]);
        }
        a = 0;
      }
    }
    bin.insert(bin.end(), pad.begin(), pad.end());
  }
}
//-----
std::string to_hex(std::string &value)//converting binary to hexadecimal
{
  std::string result = "";
  for (size_t i = 0; i != value.length(); i += 4)
  {
    std::bitset<4> binary(value.substr(i, 4));
    std::stringstream hash;
    hash << std::hex << binary.to_ulong();
    result += hash.str();
  }
  return result;
}
//------
std::string combine_hash_function (std::string input)
{
  std::vector<int> bin;
  if (input == "")//forcing to give an output even though the text file is empty
  {
      std::string efl = "asgashaspgbansfasfsa6gds4hsdhsd6ags5g4sagagasasgsdgQagasgaAHSFASfsfafasfs";
      to_bin(efl, bin);
  }
  else
  {
      to_bin(input, bin);
  }
  padding(bin);
  std::string value = mixing_bin(bin);
  std::string output = to_hex(value);
  return output;

}
//-----------------
std::string rand_str (const int length)//https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c/440240
{
    static const char alpha[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string rand_txt;

    for (int i = 0; i < length; ++i)
    {
        rand_txt += alpha[rand() % (sizeof(alpha) - 1)];
    }
    return rand_txt;
}
//-----------------
void test1 (const int length)
{
  unsigned int coll = 0;
  for (size_t i = 0; i != 25000; ++i)
  {
    std::string t1 = rand_str(length);
    std::string t2 = rand_str(length);
    if (combine_hash_function(t1) == combine_hash_function(t2))
    {
      coll++;
    }
  }
  std::cout << "Collisions found (length " << length << ") ->  " << coll << std::endl;
}
//-----------------
void test2() //checking hashes only, because in order to check binary codes, i'd have to refactor a lot of stuff
{
  std::vector<int> A;
  unsigned int coll = 0, it;
  unsigned int a = 0, min, max;
  std::string t1, t2, tt1, tt2, letter, bin1, bin2;
  double total;
  std::vector<int> bin;
  for (size_t i = 0; i != 100000; ++i)
  {
    t1 = rand_str(5);
    t2 = t1;
    while(t1 == t2)
    {
      it = rand() % 10;
      letter = rand_str(1);
      t2[it] = letter[0];
    }
    //getting hashes
    tt1 = combine_hash_function(t1);
    tt2 = combine_hash_function(t2);
    if (tt1 == tt2)
    {
      coll++;//looking for collisions
    }
    for (size_t j = 0; j != tt1.length(); ++j)
    {
      if (tt1[j] == tt2[j])
      {
        a++;
      }
    }
    A.push_back(a);
    a = 0;
  }
  std::cout << "Collisions found -> " << coll << std::endl;
  std::cout << std::fixed << std::setprecision(2) << "Minimum  ->" << 100 - (double(*std::min_element(A.begin(), A.end())) / double(tt1.length()) * 100) << std::endl;
  std::cout << std::fixed << std::setprecision(2) << "Maximum  ->" << 100 - (double(*std::max_element(A.begin(), A.end())) / double(tt1.length()) * 100) << std::endl;
  for (size_t i = 0; i != A.size(); ++i)
  {
    total += A[i];
  }
  std::cout << "Average  ->" << std::fixed << std::setprecision(2) << 100 - (((total / (tt1.length() * 1.0)) / 100000) * 100) << std::endl;
}
