#ifndef PWM_H
#define PWM_H

#include "gpio.h"
#include <thread>

class PWM
{

  public:
    PWM(GPIOIf *gpio,
        unsigned int frequency,
        unsigned int dutyCycle);

    ~PWM();

    void start();

    void stop();

  private:

    void runnable();

    std::thread m_thread;
    GPIOIf *m_gpio;
    unsigned int m_frequency;
    unsigned int m_dutyCycle;
    bool m_isRunning;
};
#endif // PWM_H
