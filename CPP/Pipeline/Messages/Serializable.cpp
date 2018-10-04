#include "Serializable.h"

namespace Pipeline
{
  namespace Messages
  {


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
        /*
           size_t length;
           source = SerializablePlainOldData<size_t>::deserialize(source, length);
           target = new char[length*2];
           memcpy(&target, source, length);
           return source + size(target);
         */
      }
  }
}
