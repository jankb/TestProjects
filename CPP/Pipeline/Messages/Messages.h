#pragma once
#ifndef PIPELINE_MESSAGES_MESSAGE_H
#define PIPELINE_MESSAGES_MESSAGE_H

#include "Serializable.h"

namespace Pipeline
{
  namespace Messages 
  {
    class Message : public Serializable
    {
    public:
      Message(void);
      virtual ~Message(void);

      virtual size_t size() const;
      virtual char* serialize(char* dataOut) const;
      virtual char* deSerialize(char* dataIn);

      int m_stationId;
      int m_messageId;
    };

    class OpenPort : public Message
    {
    public:
      OpenPort(void) {};
      virtual ~OpenPort(void) {};

      virtual size_t size() const;
      virtual char* serialize(char* dataOut) const;
      virtual char* deSerialize(char* dataIn);

      int m_port;
      char* m_message;
      int m_sum;
    };
  }
}
#endif
