#include "tokenizer.h"
#include "gtest/gtest.h"

#include <string>

void testTokenEquality(Token&, Token&);

TEST(Tokenizer, nextTokenTest) {
  std::string testLine {" hold My beer    "};
  Token expectedToken[3] {
    {TokenType::Content, "hold"},
    {TokenType::Content, "my"},
    {TokenType::Content, "beer"}
  };

  Tokenizer t(testLine);

  for (int i {0}; i < 3; ++i) {
    ASSERT_TRUE(t.nextToken());
    Token gotToken {t.currToken()};
    testTokenEquality(gotToken, expectedToken[i]);
  }

  ASSERT_FALSE(t.nextToken());
}

TEST(HtmlTokenize, singleHtmlTagTest) {
  std::string testHtml {"<!DOCTYPE html>"};
  Token expectedToken {TokenType::DocType, "html"};

  Tokenizer t(testHtml);

  ASSERT_TRUE(t.nextToken());
  Token tk = t.currToken();
  testTokenEquality(tk, expectedToken);
}

TEST(HtmlTokenize, complexHtmlTagTest) {
  std::string testHtml {R"(<!DOCTYPE html>
<html>
  <head>
  </head>
  <body class="mc">
    <p>Hello world!</p>
  </body>
</html>)"};

  Token expectedToken[11] {
    {TokenType::DocType, "html"},
    {TokenType::HtmlBegin, ""}, {TokenType::HeadBegin, ""},
    {TokenType::HeadEnd, ""}, {TokenType::BodyBegin, "class=\"mc\""},
    {TokenType::ParagBegin, ""}, {TokenType::Content, "hello"},
    {TokenType::Content, "world!"}, {TokenType::ParagEnd, ""},
    {TokenType::BodyEnd, ""}, {TokenType::HtmlEnd, ""}
  };

  Tokenizer t(testHtml);

  Token tk;
  int i {0};
  while (t.nextToken()) {
    tk = t.currToken();
    testTokenEquality(tk, expectedToken[i]);
    i++;
  }

  EXPECT_EQ(i, 11);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void testTokenEquality(Token &got, Token &expected) {
  EXPECT_EQ(got.type, expected.type);
  EXPECT_EQ(got.value, expected.value);
}
