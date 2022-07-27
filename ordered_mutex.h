#ifndef ORDERED_MUTEX_H_
#define ORDERED_MUTEX_H_

#include <condition_variable>
#include <mutex>

class OrderedMutex {
 public:
  OrderedMutex() = default;
  ~OrderedMutex() = default;
  OrderedMutex(const OrderedMutex&) = delete;
  OrderedMutex& operator=(const OrderedMutex&) = delete;

  void lock() {
    std::unique_lock<std::mutex> lock(mutex_);
    const auto req = head_++;
    cond_.wait(lock, [&] { return req == tail_; });
  }

  void unlock() {
    std::unique_lock<std::mutex> lock(mutex_);
    ++tail_;
    cond_.notify_all();
  }

 private:
  int head_ = 0;
  int tail_ = 0;

  std::mutex mutex_;
  std::condition_variable cond_;
};

#endif  // ORDERED_MUTEX_H_
