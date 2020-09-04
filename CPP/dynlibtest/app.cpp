// Simple application that loads a lib to insert 
// test values.
#include <iostream>
#include <dlfcn.h>

int main()
{
  std::cout << "Starting ..." << std::endl;

  std::string greeting = "Hello world from ";

  // Try to open the library .so file
  void* libHandle = dlopen("./libtestlib.so",RTLD_NOW);
  
  // If the file is not found, or for some reason unable to open
  // run "production" code
  if (libHandle == nullptr)
  {
    greeting += "actual code";
  }
  // If the test lib _is_ found, we will use the test values.
  else
  {
    // Function pointer that matches the signature of the method 
    // we want to load.
    typedef std::string(*testfunction)();

    // Try to load the function from the library. 
    testfunction func = (testfunction)dlsym(libHandle, "testValue");
    // Consider inserting some errorhandling here.

    // Call the loaded function and use the test values.
    greeting += func();
  }
  std::cout << greeting << std::endl;
  return 0;
}
