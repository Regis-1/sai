#pragma once

#include <string>
#include <filesystem>

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
  explicit Tokenizer(std::string &source);
  explicit Tokenizer(std::filesystem::path &path);

  bool nextToken();
  Token currToken() const;
  bool isFileLoaded() const;

private:
  std::string::iterator it_;
  std::string::iterator end_;
  std::string fileContent_;
  
  Token currToken_;

  void extractToken();
  bool isWhitespace() const;
  bool isOmitPunctuation() const;
  bool isHtmlEntity() const;

  Token parseContent();
  Token parseTag();
  TokenType detectType(std::string &tw);
};
