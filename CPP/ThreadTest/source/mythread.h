#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <pthread.h>

class myThread
{
public:
  myThread();

  void run();

  pthread_t threadId();

  static void *start(void* arg);

  virtual void doWork() = 0;

private:
  pthread_t m_thread;
};

#endif // MYTHREAD_H
