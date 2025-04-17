#pragma once

#include <unordered_map>
#include <string>

class Tokenizer;

class Indexer {
 public:
  std::unordered_map<std::string, int> index;

  Indexer();
  void UpdateIndex(Tokenizer &t);
};
