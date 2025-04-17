#include "tokenizer.h"
#include "indexer.h"
#include "gtest/gtest.h"

TEST(Indexer, ignoreNotRevelantContentTest) {
  std::string testString {R"(<head>
  <script>let x = 5; alert(x);</script>
</head>
<h1>Hello world</p>
<td><div>Defined in header <code>
<a href="../../header/cmath.html" title="cpp/header/cmath">&lt;cmath&gt;</a>
</code></div></td>)"};

  std::string expectContent[] {
    "hello", "world", "defined", "in", "header", "cmath"
  };

  Tokenizer t(testString);
  Indexer indexer;

  indexer.UpdateIndex(t);

  for (auto &expected : expectContent) {
    auto search = indexer.index.find(expected);
    EXPECT_TRUE(search != indexer.index.end()) << "Word: " << expected;
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
