#include <iostream>
#include <dlfcn.h>

int main()
{
  std::cout << "Starting ..." << std::endl;

  void* libHandle = nullptr;
  libHandle = dlopen("./libtestlib.so",RTLD_NOW);
  std::string greeting = "Hello world from ";
  if (libHandle == nullptr)
  {
    greeting += "actual code";
  }
  else
  {
    typedef std::string(*testfunction)();
    testfunction func = (testfunction)dlsym(libHandle, "testValue");
    const char* err = dlerror();
    if(err)
    {
      printf("could not dlsym: %s\n",err);
      return 0;
    } 
    greeting += func();
  }
  std::cout << greeting << std::endl;
  return 0;
}
