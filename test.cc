#include <mutex>
#include <thread>
#include <vector>

#include "iutest/include/iutest.hpp"
#include "ordered_mutex.h"

IUTEST_MAKE_PEEP(int OrderedMutex::*, OrderedMutex, head_);

IUTEST(test, test_0) {
  OrderedMutex mutex;
  int x = IUTEST_PEEP_GET(mutex, OrderedMutex, head_);
  IUTEST_ASSERT_EQ(0, x);

  mutex.lock();
  x = IUTEST_PEEP_GET(mutex, OrderedMutex, head_);
  IUTEST_ASSERT_EQ(1, x);

  mutex.unlock();
}

IUTEST(test, test_1) {
  OrderedMutex mutex;
  std::vector<std::thread> ths;
  const int N = 1000;
  int data = 0;

  for (int i = 0; i < N; ++i) {
    ths.emplace_back([&] {
      std::unique_lock<OrderedMutex> lock(mutex);
      ++data;
    });
  }

  for (auto& t : ths) {
    t.join();
  }

  IUTEST_ASSERT_EQ(N, data);
}

int main(int argc, char* argv[]) {
  IUTEST_INIT(&argc, argv);
  return IUTEST_RUN_ALL_TESTS();
}
