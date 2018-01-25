#include "gpio.h"
#include <iostream>
#include <thread>
#include <chrono>

class PWM 
{

  public:
    PWM(GPIOIf *gpio, unsigned int frequency, unsigned int dutyCycle) 
      : m_gpio(gpio),
      m_frequency(frequency),
      m_dutyCycle(dutyCycle),
      m_isRunning(false)
  {}
    void start()
    {
      m_thread = std::thread(&PWM::runnable,this);
      m_isRunning = true;
    }

    void stop()
    {
      m_isRunning = false;
    }

  private:

    void runnable()
    {
      std::cout << "Starting runnable." << std::endl;
      while (m_isRunning)
      {
        m_gpio->turnOn();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        m_gpio->turnOff();
      }
      std::cout << "Stopped runnable." << std::endl;
    }

    std::thread m_thread;
    GPIOIf *m_gpio;
    unsigned int m_frequency;
    unsigned int m_dutyCycle;
    bool m_isRunning;
};

int main()
{
  std::cout << "Starting." << std::endl;
  GPIO gpio(13,GPIO::OUT);
  gpio.turnOff();
  int value;
  std::cin >> value;
  gpio.turnOn();
  return 0;
}
