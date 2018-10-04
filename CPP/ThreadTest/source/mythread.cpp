#include "mythread.h"
#include <iostream>

myThread::myThread()
{
}

void myThread::run()
{
  int rc = 0;
  if ((rc = pthread_create(&m_thread, NULL, myThread::start, this)))
  {
    std::cout << "Error creating thread : " << rc;
    return;
  }
  std::cout << "Started thread " << m_thread << std::endl;
}

pthread_t myThread::threadId()
{
  return m_thread;
}

void *myThread::start(void* arg)
{
  myThread *data = (myThread*)arg;
  std::cout << "Calling doWork on thread " << data->threadId() << std::endl;
  data->doWork();
  pthread_exit(NULL);
}


