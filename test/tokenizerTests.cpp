#include "tokenizer.h"
#include "gtest/gtest.h"

TEST(SimpleSuite, simpleTest) {
  EXPECT_FALSE(true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
