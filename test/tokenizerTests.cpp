#include "tokenizer.h"
#include "gtest/gtest.h"

void testTokenEquality(Token&, Token&);
int testTokenArray(Tokenizer&, Token*);

namespace {
  Token expectedSimpleToken[11] {
    {TokenType::DocType, "html"},
    {TokenType::HtmlBegin, ""}, {TokenType::HeadBegin, ""},
    {TokenType::HeadEnd, ""}, {TokenType::BodyBegin, "class=\"mc\""},
    {TokenType::ParagBegin, ""}, {TokenType::Content, "hello"},
    {TokenType::Content, "cmath"}, {TokenType::ParagEnd, ""},
    {TokenType::BodyEnd, ""}, {TokenType::HtmlEnd, ""}
  };
}

TEST(Tokenizer, nextTokenTest) {
  std::string testLine {" hold, My beer.    "};
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

TEST(HtmlTokenize, tokenizeHtmlFileTest) {
  std::filesystem::path filePath {"./test/simpleHtml.html"};

  Tokenizer t(filePath);

  ASSERT_TRUE(t.isFileLoaded()) << "ERROR: File wasn't loaded correctly";
  int i {testTokenArray(t, expectedSimpleToken)};
  EXPECT_EQ(i, 11);
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
    <p>Hello &lt;cmath&gt!</p>
  </body>
</html>)"};

  Tokenizer t(testHtml);

  int i {testTokenArray(t, expectedSimpleToken)};

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

int testTokenArray(Tokenizer &t, Token *expArr) {
  Token tk;
  int i {0};
  while (t.nextToken()) {
    tk = t.currToken();
    testTokenEquality(tk, expArr[i]);
    i++;
  }

  return i;
}
