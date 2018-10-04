#include "Pipe.h"

using namespace Pipeline;

Pipe::Pipe(void)
{
}


Pipe::~Pipe(void)
{
}
//
//void Pipe::send(Messages::Message* message)
//{
//  Messages::Message* tmp = message;
//  int a = 2;
//}

void Pipe::send(const Pipeline::Messages::Serializable& message)
{
  size_t data_length =  message.size();
  char *outData = new char[data_length*2];
 // char *start = outData;
  message.serialize(outData);
 //
 // delete[] outData;


  Pipeline::Messages::OpenPort msg;
//  char *inData = new char[data_length];
  msg.deSerialize(outData);
  
    delete[] outData;
//   int b = 13;
}
