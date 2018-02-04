#include <iostream>
#include <chrono>
#include "pwm.h"

PWM::PWM(GPIOIf *gpio,
         unsigned int frequency,
         float dutyCycle)
  : m_gpio(gpio),
  m_frequency(frequency),
  m_dutyCycle(dutyCycle),
  m_isRunning(false)
{
    m_totalTime = 1000 / m_frequency;
    m_timing.on = m_totalTime * m_dutyCycle;
    m_timing.off = m_totalTime - m_timing.on;
    std::cout << "Dutycycle startup  : " << m_dutyCycle << " on : " << m_timing.on << " off : " << m_timing.off << std::endl;
}

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

void PWM::setDutyCycle(float dutyCycle)
{
  m_dutyCycle = dutyCycle;
  m_timing.on  = m_totalTime * m_dutyCycle;
  m_timing.off = m_totalTime - m_timing.on;
//  std::cout << "Dutycycle is now  : " << m_dutyCycle << " on : " << m_timing.on << " off : " << m_timing.off << std::endl;
}

void PWM::runnable()
{
  std::cout << "Starting runnable." << std::endl;
  std::cout << "Total time : " << m_totalTime << std::endl;
  std::cout << "Dutycycle  : " << m_dutyCycle << " on : " << m_timing.on << " off : " << m_timing.off << std::endl;
  while (m_isRunning)
  {
    m_gpio->turnOn();
    std::this_thread::sleep_for(std::chrono::milliseconds(m_timing.on));
    m_gpio->turnOff();
    std::this_thread::sleep_for(std::chrono::milliseconds(m_timing.off));


  }
  std::cout << "Stopped runnable." << std::endl;
}
