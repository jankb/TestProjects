// Pipeline.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "Pipe.h"
#include "Messages.h"

template <typename someType>
char* appendToChar(char* target, someType t)
{
  size_t t_length = sizeof t;
  memcpy(target, &t, t_length);
  return target + t_length;
}

template <typename someType>
char* extractFromChar(char* source, someType &t)
{
  size_t t_length = sizeof t;
  memcpy(&t, source, t_length);
  return source + t_length;
}


size_t sizeOfChar(char* str)
{
   return sizeof(size_t) + strlen(str);
}

template<>
char* appendToChar<char*>(char* target, char* t)
{
  size_t t_length = sizeOfChar(t);
  target = appendToChar<size_t>(target,strlen(t));
  memcpy(target, &t, strlen(t));
  return target + t_length;
}

template<>
char* extractFromChar<char*>(char* source, char*& t)
{
  size_t lengthOfCharP;
  source = extractFromChar<size_t>(source, lengthOfCharP);
  memcpy(&t, source, lengthOfCharP);
  return source + lengthOfCharP;
}

int main(int argc, char* argv[])
{
  std::cout << "Starting Pipeline test...." << std::endl;
/*
  char* start;

  {
    int a = 666;
    int b = 42;
    double c = 123.4;
    char* txt = "/deb/port";

    size_t totalSize = sizeof(a)+ sizeof(b) + sizeof(c) + sizeOfChar(txt);
    char* target = new char[totalSize];
    start = target;

    printf("Char has value : %c, addr : %p\n", *target, target);
    target = appendToChar<int>(target, a);
    target = appendToChar<int>(target, b);
    target = appendToChar<double>(target, c);
    target = appendToChar<char*>(target, txt);
    printf("Char has value : %i, addr : %p\n", *target, target);
  }

  {
    int a;
    int b;
    double c;
    char* txt;
    start = extractFromChar<int>(start, a);
    start = extractFromChar<int>(start, b);
    start = extractFromChar<double>(start, c);
    start = extractFromChar<char*>(start, txt);

    int hnngh = 123;
  }
  */

  Pipeline::Messages::OpenPort openPort;
  openPort.m_stationId = 13;
  openPort.m_messageId = 666;
  openPort.m_port = 10;
  openPort.m_message = "/dev/myport/";
  openPort.m_sum = 1234;

  Pipeline::Pipe pipe;

  pipe.send(openPort);

	return 0;
}

