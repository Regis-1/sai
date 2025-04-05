#include "tokenizer.h"
#include "gtest/gtest.h"

#include <string>

TEST(Tokenizer, nextTokenTest) {
  std::string testLine {" hello from the other side  "};
  std::string expectedToken[5] {"hello", "from", "the", "other", "side"};

  Tokenizer t(testLine);

  for (int i {0}; i < 5; ++i) {
    ASSERT_TRUE(t.nextToken());
    std::string gotToken {t.currToken()};
    EXPECT_EQ(gotToken, expectedToken[i]);
  }

  ASSERT_FALSE(t.nextToken());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
