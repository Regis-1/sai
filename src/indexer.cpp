#include "indexer.h"
#include "tokenizer.h"

Indexer::Indexer() : index() {
}

void Indexer::UpdateIndex(Tokenizer &t) {
  /*
    1. get tokens from tokenizer & control the flag regarding the reading
    2. if Content and reading_flag == true, then get the token
    3. perform token formatting
    4. put token into the index map as a key and increase its count
   */
}
