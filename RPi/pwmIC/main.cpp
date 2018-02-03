#include "gpio.h"
#include "pwm.h"
#include <iostream>

int main()
{
  std::cout << "Starting." << std::endl;
  GPIO *gpio = new GPIO(13,GPIO::OUT);
  PWM pwm(gpio, 50, 50);
  pwm.start();
//  gpio.turnOff();
  int value;
  std::cin >> value;
  pwm.stop();
  delete gpio;
 // gpio.turnOn();
  return 0;
}
