#include "tokenizer.h"
#include <cctype>

Tokenizer::Tokenizer(std::string &source)
  : it_(source.begin()), end_(source.end()), currToken_("") {

}

bool Tokenizer::nextToken() {
  while (isWhitespace()) {
    it_++;

    if (it_ == end_)
      return false;
  }

  extractToken();
  return true;
}

std::string Tokenizer::currToken() {
  return currToken_;
}

void Tokenizer::extractToken() {
  std::string result {""};
  while (!isWhitespace()) {
    result += *it_;
    it_++;
  }

  currToken_ = result;
}

bool Tokenizer::isWhitespace() {
  if (std::isspace(*it_) != 0)
    return true;

  return false;
}
