// A very simple and small "library", but it proves the point.
#include <string>

extern "C" // Needed to "unmangle" symbols so that dlsym can find them
{
  std::string testValue()
  {
    return "test lib";
  }
}
