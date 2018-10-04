#pragma once
#ifndef PIPELINE_PIPE_H
#define PIPELINE_PIPE_H
#include "Messages.h"

namespace Pipeline
{
  class Pipe
  {
    public:
      Pipe(void);
      ~Pipe(void);

      // void send(Pipeline::Messages::Message* message);

      void send(const Pipeline::Messages::Serializable& message);
  };
}
#endif
