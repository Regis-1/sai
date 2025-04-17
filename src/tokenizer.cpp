#include "tokenizer.h"
#include <cctype>
#include <algorithm>
#include <fstream>
#include <iterator>

Tokenizer::Tokenizer(std::string &source)
  : it_(source.begin()), end_(source.end()), fileContent_(),
    currToken_({TokenType::Null, ""}) {

}

Tokenizer::Tokenizer(std::filesystem::path &path)
  : fileContent_("") {

  std::ifstream fd(path, std::ios::in | std::ios::binary);

  if (!fd.is_open())
    return;

  const auto fileSize {std::filesystem::file_size(path)};
  fileContent_.resize(fileSize);
  fd.read(fileContent_.data(), fileSize);

  fd.close();

  it_ = fileContent_.begin();
  end_ = fileContent_.end();
}

bool Tokenizer::nextToken() {
  while (isWhitespace() || isOmitPunctuation()) {
    it_++;
  }

  if (it_ == end_)
    return false;

  extractToken();
  return true;
}

Token Tokenizer::currToken() const {
  return currToken_;
}

void Tokenizer::extractToken() {
  if (*it_ == '<')
    currToken_ = parseTag();
  else
    currToken_ = parseContent();
}

bool Tokenizer::isWhitespace() const {
  if (std::isspace(*it_) != 0)
    return true;

  return false;
}

bool Tokenizer::isOmitPunctuation() const {
  const unsigned int c {(unsigned int)*it_};
  if ((33 <= c && c < 37) || (39 <= c && c < 45) ||
      (46 <= c && c < 48) || (63 <= c && c < 65))
    return true;

  return false;
}

bool Tokenizer::isFileLoaded() const {
  if (fileContent_ == "") {
    return false;
  }
  
  return true;
}

Token Tokenizer::parseContent() {
  std::string value {""};
  
  while (!isWhitespace() && !isOmitPunctuation() && *it_ != '<') {
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
