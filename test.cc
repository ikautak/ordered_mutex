#include "iutest/include/iutest.hpp"

IUTEST(test, test_0) {
  int x = 0;
  IUTEST_ASSERT_EQ(x, 0);
}

int main(int argc, char* argv[]) {
  IUTEST_INIT(&argc, argv);
  return IUTEST_RUN_ALL_TESTS();
}
