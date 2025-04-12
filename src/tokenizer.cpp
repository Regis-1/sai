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
    value += std::tolower(*it_);

    it_++;
    if (it_ == end_)
      break;
  }

  return {TokenType::Content, value};
}

Token Tokenizer::parseTag() {
  std::string typeWord {""};

  while (!isWhitespace() && *it_ != '>') {
    typeWord += std::tolower(*it_);

    it_++;
    if (it_ == end_)
      break;
  }

  TokenType type = detectType(typeWord);
  std::string value {""};

  if (*it_ != '>') {
    it_++;
    while (it_ != end_ && *it_ != '>') {
      value += *it_;
      it_++;
    }
  }

  it_++;
  return {type, value};
}

TokenType Tokenizer::detectType(std::string &tw) {
  if (tw == "<!doctype")
    return TokenType::DocType;
  else if (tw == "<html")
    return TokenType::HtmlBegin;
  else if (tw == "</html")
    return TokenType::HtmlEnd;
  else if (tw == "<p")
    return TokenType::ParagBegin;
  else if (tw == "</p")
    return TokenType::ParagEnd;
  else if (tw == "<body")
    return TokenType::BodyBegin;
  else if (tw == "</body")
    return TokenType::BodyEnd;
  else if (tw == "<head")
    return TokenType::HeadBegin;
  else if (tw == "</head")
    return TokenType::HeadEnd;
  
  return TokenType::Null;
}
