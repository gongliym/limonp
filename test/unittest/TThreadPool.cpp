#include "gtest/gtest.h"
#include "ThreadPool.hpp"
#include <exception>
using namespace limonp;

//static void addOne(void * data)
//{
//    size_t * i = (size_t *) data;
//    (*i) ++;
//}

class Task: public ITask {
 public:
  Task(size_t& i): i_(i) {
  }
 public:
  size_t& i_;
 public:
  virtual void run() {
    i_++;
  }
};

class Exception: public exception {
 public:
  Exception(const string& error)
    : error_(error) {
  }
  virtual ~Exception() throw() {
  }
  virtual const char* what() const throw() {
    return "hello Exception";
  }
 private:
  string error_;
};

class TaskWithException: public ITask {
 public:
  TaskWithException() {
  }
  virtual void run() {
    throw Exception("hello exception!!!");
  }
};

TEST(ThreadPool, Test1) {
  const size_t threadNum = 2;
  const size_t queueMaxSize = 4;
  vector<size_t> numbers(6);
  {
    ThreadPool threadPool(threadNum, queueMaxSize);
    threadPool.start();
    for(size_t i = 0; i < numbers.size(); i ++) {
      numbers[i] = i;
      threadPool.add(CreateTask<Task, size_t& >(numbers[i]));
    }
  }
  for(size_t i = 0; i < numbers.size(); i++) {
    ASSERT_EQ(i + 1, numbers[i]);
  }
}

TEST(ThreadPool, Exception) {
  const size_t threadNum = 2;
  const size_t taskLimit = 4;
  ThreadPool threadPool(threadNum, taskLimit);
  threadPool.start();
  
  threadPool.add(CreateTask<TaskWithException>());
}
