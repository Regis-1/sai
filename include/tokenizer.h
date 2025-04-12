#pragma once

#include <string>

enum class TokenType {
  Null,
  Content,
  DocType,
  HtmlBegin, HtmlEnd,
  ParagBegin, ParagEnd,
  BodyBegin, BodyEnd,
  HeadBegin, HeadEnd
};

struct Token {
  TokenType type;
  std::string value;
};

class Tokenizer {
public:
  Tokenizer(std::string &source);

  bool nextToken();
  Token currToken();

private:
  std::string::iterator it_;
  std::string::iterator end_;
  
  Token currToken_;

  void extractToken();
  bool isWhitespace();

  Token parseContent();
  Token parseTag();
  TokenType detectType(std::string &tw);
};
