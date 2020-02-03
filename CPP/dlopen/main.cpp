#include <dlfcn.h>
#include <iostream>

void* handle;
int (*sum)(int, int);
char *error;
int main()
{
  std::cout << "Starting... " << std::endl;

  handle = nullptr;
  handle = dlopen("./libmathtest.so.1.0", RTLD_NOW);
  if (!handle)
  {
    std::cout << "Error opening voff: " << dlerror() << std::endl;
  }

  *(void**)(&sum) = dlsym(handle, "sum");
  if ((error = dlerror()) != NULL)  {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }
  int res = (*sum)(2,2);

  std::cout << "Result is " << res << std::endl;
  std::cout << "Done... " << std::endl;
  return 0;
}
