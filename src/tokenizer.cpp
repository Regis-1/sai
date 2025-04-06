#include "tokenizer.h"
#include <cctype>
#include <algorithm>

Tokenizer::Tokenizer(std::string &source)
  : it_(source.begin()), end_(source.end()),
    currToken_({TokenType::Null, ""}) {

}

bool Tokenizer::nextToken() {
  while (isWhitespace()) {
    it_++;
  }

  if (it_ == end_)
    return false;

  extractToken();
  return true;
}

Token Tokenizer::currToken() {
  return currToken_;
}

void Tokenizer::extractToken() {
  if (*it_ == '<')
    currToken_ = parseTag();
  else
    currToken_ = parseContent();
}

bool Tokenizer::isWhitespace() {
  if (std::isspace(*it_) != 0)
    return true;

  return false;
}

Token Tokenizer::parseContent() {
  std::string value {""};
  
  while (!isWhitespace() && *it_ != '<') {
    value += *it_;

    it_++;
    if (it_ == end_)
      break;
  }

  return {TokenType::Content, value};
}

Token Tokenizer::parseTag() {
  std::string typeWord {""};

  while (!isWhitespace() && *it_ != '>') {
    typeWord += *it_;

    it_++;
    if (it_ == end_)
      break;
  }

  std::transform(typeWord.begin(), typeWord.end(), typeWord.begin(),
		 [](unsigned char c){ return std::tolower(c); }
		);
  
  TokenType type = detectType(typeWord);
  std::string value {""};

  while (true) {
    it_++;
    
    if (it_ == end_ || *it_ == '>')
      break;
    
    value += *it_;
  }

  if (*it_ == '>')
    it_++;

  return {type, value};
}

TokenType Tokenizer::detectType(std::string &tw) {
  if (tw == "<!doctype") {
    return TokenType::DocType;
  }
  
  return TokenType::Null;
}
