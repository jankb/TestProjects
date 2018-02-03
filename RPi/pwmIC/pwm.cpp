#include <iostream>
#include <chrono>
#include "pwm.h"

PWM::PWM(GPIOIf *gpio, unsigned int frequency, unsigned int dutyCycle)
  : m_gpio(gpio),
  m_frequency(frequency),
  m_dutyCycle(dutyCycle),
  m_isRunning(false)
{}

PWM::~PWM()
{
    m_thread.join();
}

void PWM::start()
{
  m_thread = std::thread(&PWM::runnable,this);
  m_isRunning = true;
}

void PWM::stop()
{
  m_isRunning = false;
}

void PWM::runnable()
{
  std::cout << "Starting runnable." << std::endl;
  while (m_isRunning)
  {
    m_gpio->turnOn();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    m_gpio->turnOff();
    std::this_thread::sleep_for(std::chrono::milliseconds(13));


  }
  std::cout << "Stopped runnable." << std::endl;
}
