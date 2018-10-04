#include "greeting.h"
#include <iostream>

greeting::greeting()
{
  std::cout << "Ctor EN." << std::endl;
}

void greeting::sayHello()
{
  std::cout << "Hello from EN." << std::endl;
}
