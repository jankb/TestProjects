#include <iostream>
#include "greeting.h"

int main()
{
  std::cout << "Starting lib Test App..." << std::endl;
  greeting *g = new greeting();
  g->sayHello();
  return 0;
}
