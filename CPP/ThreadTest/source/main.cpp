#include <iostream>
#include <bitset>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sstream>
#include "bubblesort.h"
#include "mythread.h"

#define NUM_THREADS 10

class STATUS
{
public:
  enum values{
    RED = 1,
    YELLOW = 2,
    GREEN = 4,
    RUNNING = 8,
    STARTING = 16,
    STOPPED = 32
  };

};

class Engine
{
public:
  Engine() : m_status(0)
  {}

  void setStatus(int s)
  {
    m_status |= s;
  }

  int status()
  {
    return m_status;
  }

private:

  int m_status;
};
/*
int main()
{



  int operational = STATUS::GREEN  | STATUS::RUNNING;
  int failed      = STATUS::RED    | STATUS::STOPPED;
  int stopped     = STATUS::GREEN  | STATUS::STOPPED;
  int degraded    = STATUS::YELLOW | STATUS::RUNNING;

  Engine e;
  std::cout << "Status : " << e.status() << std::endl;
  e.setStatus(operational);
  std::cout << "Status : " << e.status() << std::endl;
  e.setStatus(degraded);
  std::cout << "Status : " << e.status() << std::endl;

  int status = e.status();

  if (status & STATUS::RED)
  {
    std::cout << "Status Found: " << e.status() << std::endl;
  }
  
  
  return 0;
}
*/
/*
typedef struct _thread_data_t {
    int tid;
    double stuff;
} thread_data_t;
*/

//int num = 0;

struct Person
{
  Person()
  {
    firstname = "not-set";
    lastname = "not-set";
  }

  std::string firstname;
  std::string lastname;
};

class DataStore
{
public:
  DataStore()
  {
    pthread_mutex_init(&lock, NULL);
    std::cout << "Data::Data data is : " << m_data.firstname << ", " << m_data.lastname << std::endl<< std::flush;
  }

  void set(Person data)
  {
 //   std::cout << "Data::set data set to : "  << data.firstname << ", " << data.lastname<< std::endl<< std::flush;
 //   std::cout << "Data::set lock "<<std::endl;

//    while (0 != pthread_mutex_trylock(&lock))
//    {
//      std::cout << "Data::set waiting for lock" << std::endl;
//      usleep(3);
//    }

//  //  std::cout << "Data::set data set to : " << i  <<std::endl;
    pthread_mutex_lock(&lock);
    m_data.firstname = data.firstname;
   usleep(1000);
    m_data.lastname = data.lastname;
  //  std::cout << "Data::set unlock "<<std::endl;
    pthread_mutex_unlock(&lock);
  }

  Person get()
  {
    Person tmp;
    while (0 != pthread_mutex_trylock(&lock))
    {
     //  std::cout << "Data::get waiting for lock" << std::endl;
      pthread_yield();
    }
    tmp = m_data;
    pthread_mutex_unlock(&lock);

  //  std::cout << "Data::get" << std::endl<< std::flush;
    return tmp;
  }

private:
  pthread_mutex_t lock;
  Person m_data;
};

class displayThread : public myThread
{
public:
  void setData(DataStore* d)
  {
    m_data = d;
  }

  void doWork()
  {
    while(1)
    {
      Person p = m_data->get();
      std::cout << "-------------------------------------------" << std::endl << std::flush;
      std::cout << "Firstname is " <<  p.firstname << std::endl << std::flush;
      std::cout << "Lastname is  " <<  p.lastname << std::endl << std::flush;
      pthread_yield();
      //usleep(5);
    }
  }

private:
  DataStore* m_data;
};

class incThread : public myThread
{
public:
  void setData(DataStore* d)
  {
    m_data = d;
  }

  void doWork()
  {
    int i = 0;
    while(1)
    {
      std::stringstream ss;
      ss << i++;
      Person tmp;
      tmp.firstname = ss.str();
      tmp.lastname = ss.str();
      m_data->set(tmp);
      pthread_yield();
      //usleep(5);
    }
  }

private:
  DataStore* m_data;
};

class sortThread : public myThread
{
public:
  sortThread(BubbleSort::dataType items)
  {
    m_bs = new BubbleSort(items);
  }

  void doWork()
  {
    m_bs->sort();
  }
private:
  BubbleSort *m_bs;
};


int main()
{
  std::cout << "Starting thread test." << std::endl;

  sortThread s1(140000);
 s1.run();

 sleep(2);
 sortThread s2(140000);
 s2.run();

 sleep(2);
 sortThread s3(140000);
 s3.run();

 sleep(2);
 sortThread s4(140000);
 s4.run();

   pthread_join(s1.threadId(), NULL);
   pthread_join(s2.threadId(), NULL);

   pthread_join(s3.threadId(), NULL);
   pthread_join(s4.threadId(), NULL);


//  DataStore *d = new DataStore();

//  displayThread mt;
//  mt.setData(d);
//  mt.run();

//  incThread inc;
//  inc.setData(d);
//  inc.run();

//  pthread_join(mt.threadId(), NULL);
//  pthread_join(inc.threadId(), NULL);



  /*
  pthread_t threads[NUM_THREADS];

  int rc;

  thread_data_t data[NUM_THREADS];

  for (int i = 0 ; i < NUM_THREADS; i++)
  {
      data[i].tid = i;
      if ((rc = pthread_create(&threads[i], NULL, run, &data[i])))
      {
          std::cout << "Error creating thread : " << rc;
          return 1;
      }
      std::cout << "Created thread : " << i <<std::endl;
  }


  for (int i = 0 ; i < NUM_THREADS; i++)
  {
      pthread_join(threads[i], NULL);
  }
*/
/*  int limit = 10000000;
  for (int i = 1; i < limit; i++)
  {
    bool isPrime = true;
    for (int j = 2; j < i; j++)
    {
      if (j == i) continue;
      int res = i % j;
      if ( res == 0)
      {
        isPrime = false;
      }
    }
    if (isPrime)
      std::cout << " " << i << " is a prime." << std::endl;
  }
*/
  return 0;
}

