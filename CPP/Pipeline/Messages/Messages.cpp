#include "Messages.h"

using namespace Pipeline::Messages;

Message::Message(void)
{
}

size_t Message::size() const
{
  return SerializablePlainOldData<int>::size(m_stationId) +
         SerializablePlainOldData<int>::size(m_messageId);
}
char* Message::serialize(char* dataOut) const
{
  dataOut = SerializablePlainOldData<int>::serialize(dataOut, m_stationId);
  dataOut = SerializablePlainOldData<int>::serialize(dataOut, m_messageId);
  return dataOut;
}

char* Message::deSerialize(char* dataIn)
{
   dataIn = SerializablePlainOldData<int>::deserialize(dataIn, m_stationId);
   dataIn = SerializablePlainOldData<int>::deserialize(dataIn, m_messageId);
   return dataIn;
}



Message::~Message(void)
{
}

size_t OpenPort::size() const
{
  return Message::size() +
    SerializablePlainOldData<int>::size(m_port) +
    SerializablePlainOldData<char*>::size(m_message) + 
    SerializablePlainOldData<int>::size(m_sum);
}

char* OpenPort::serialize(char* dataOut) const
{
  dataOut =Message::serialize(dataOut);
  dataOut = SerializablePlainOldData<int>::serialize(dataOut, m_port);
  dataOut = SerializablePlainOldData<char*>::serialize(dataOut, m_message);
  dataOut = SerializablePlainOldData<int>::serialize(dataOut, m_sum);
  return dataOut;
}

char* OpenPort::deSerialize(char* dataIn)
{
  dataIn = Message::deSerialize(dataIn);
  dataIn = SerializablePlainOldData<int>::deserialize(dataIn, m_port);
  dataIn = SerializablePlainOldData<char*>::deserialize(dataIn, m_message);
  dataIn = SerializablePlainOldData<int>::deserialize(dataIn, m_sum);
  return dataIn;
}
