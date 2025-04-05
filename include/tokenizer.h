#pragma once

#include <string>

class Tokenizer {
public:
  Tokenizer(std::string &source);

  bool nextToken();
  std::string currToken();

private:
  std::string::iterator it_;
  std::string::iterator end_;
  
  std::string currToken_;

  void extractToken();
  bool isWhitespace();
};
