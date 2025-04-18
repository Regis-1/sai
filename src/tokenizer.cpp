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
  const unsigned char c {static_cast<unsigned char>(*it_)};
  if (c == '<')
    currToken_ = parseTag();
  else
    currToken_ = parseContent();
}

bool Tokenizer::isWhitespace() const {
  return (std::isspace(*it_) != 0);
}

bool Tokenizer::isOmitPunctuation() const {
  const unsigned char c {static_cast<unsigned char>(*it_)};
  return std::ispunct(c) &&
    (c != '&' && c != '<' && c != '-');
}

bool Tokenizer::isHtmlEntity() const {
  auto it = it_;
  std::string word {""};
  unsigned char c {static_cast<unsigned char>(*it)};

  for (int i {0}; i < 3; ++i) {
    it++;
    if (it == end_)
      return false;
    
    c = static_cast<unsigned char>(*it);
    word += c;
  }

  if (word == "gt;" || word == "lt;")
    return true;

  it++;
  if (it == end_)
    return false;
  
  c = static_cast<unsigned char>(*it);
  word += c;

  if (word == "amp;")
    return true;

  return false;
}

bool Tokenizer::isFileLoaded() const {
  return !(fileContent_ == "");
}

Token Tokenizer::parseContent() {
  unsigned char c {static_cast<unsigned char>(*it_)};
  std::string value {""};
  
  while (!isWhitespace() && !isOmitPunctuation()) {
    if (c == '&' && value != "" && isHtmlEntity())
      return {TokenType::Content, value};

    value += std::tolower(c);

    it_++;
    if (it_ == end_)
      break;

    c = static_cast<unsigned char>(*it_);
  }

  return {TokenType::Content, value};
}

Token Tokenizer::parseTag() {
  unsigned char c {static_cast<unsigned char>(*it_)};
  std::string typeWord {""};

  while (!isWhitespace() && c != '>') {
    typeWord += std::tolower(c);

    it_++;
    if (it_ == end_)
      return {TokenType::Null, ""};
    
    c = static_cast<unsigned char>(*it_);
  }

  TokenType type = detectType(typeWord);
  std::string value {""};

  if (c != '>') {
    it_++;
    c = static_cast<unsigned char>(*it_);
    while (it_ != end_ && c != '>') {
      value += c;
      it_++;
      if (it_ != end_)
	c = static_cast<unsigned char>(*it_);
      else
	break;
    }
  }

  if (it_ != end_)
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
