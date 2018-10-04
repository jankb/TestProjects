#pragma once
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <cstring>

namespace Pipeline
{
  namespace Messages
  {
    class Serializable
    {
    public:
      virtual size_t size() const = 0;
      virtual char* serialize(char* dataOut) const = 0;
      virtual char* deSerialize(char* dataIn) = 0;
    };

    template <typename plainOldData>
    class SerializablePlainOldData
    {
    public:
      static size_t size(plainOldData)
      {
        return sizeof(plainOldData);
      }

      static char* serialize(char* target, plainOldData value)
      {
        memcpy(target, &value, size(value));
        return target + size(value);
      }

      static char* deserialize( char* source, plainOldData& target )
      {
        memcpy( &target, source, size(target) );
        return source + size(target);
      }
    };

    /*
    template<>
    size_t SerializablePlainOldData<char*>::size(char* str)
    {
      return sizeof(size_t) + strlen(str);
    }

    template<>
    char* SerializablePlainOldData<char*>::serialize(char* target, char* value)
    {
      target = SerializablePlainOldData<size_t>::serialize(target, strlen(value));
      memcpy(target, &value, strlen(value));
      return target + size(value);
    }

    template<>
    char* SerializablePlainOldData<char*>::deserialize(char* source, char*& target )
    {
      size_t t_length;
      memcpy(&t_length, source, sizeof(size_t));
      source = source + sizeof(size_t);
      memcpy(&target, source, t_length);
      return source + strlen(target)+ sizeof(size_t);
    //  
    //  size_t length;
    //  source = SerializablePlainOldData<size_t>::deserialize(source, length);
    //  target = new char[length*2];
    //  memcpy(&target, source, length);
    //  return source + size(target);
    //  
    }
    */
  }
}
#endif
