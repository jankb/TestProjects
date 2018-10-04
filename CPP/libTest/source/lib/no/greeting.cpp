#include "greeting.h"
#include <iostream>

greeting::greeting()
{
  std::cout << "Ctor NO." << std::endl;
}

void greeting::sayHello()
{
  std::cout << "Hallo fra NO." << std::endl;
}
