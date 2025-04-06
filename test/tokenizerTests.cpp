#include "tokenizer.h"
#include "gtest/gtest.h"

#include <string>

TEST(Tokenizer, nextTokenTest) {
  std::string testLine {" hold my beer    "};
  Token expectedToken[3] {
    {TokenType::Content, "hold"},
    {TokenType::Content, "my"},
    {TokenType::Content, "beer"}
  };

  Tokenizer t(testLine);

  for (int i {0}; i < 3; ++i) {
    ASSERT_TRUE(t.nextToken());
    Token gotToken {t.currToken()};
    EXPECT_EQ(gotToken.type, expectedToken[i].type);
    EXPECT_EQ(gotToken.value, expectedToken[i].value);
  }

  ASSERT_FALSE(t.nextToken());
}

TEST(HtmlTokenize, singleHtmlTagTest) {
  std::string testHtml {"<!DOCTYPE html>"};
  Token expectedToken {TokenType::DocType, "html"};

  Tokenizer t(testHtml);

  ASSERT_TRUE(t.nextToken());
  EXPECT_EQ(t.currToken().type, expectedToken.type);
  EXPECT_EQ(t.currToken().value, expectedToken.value);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
