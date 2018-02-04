#ifndef PWM_H
#define PWM_H

#include "gpio.h"
#include <thread>

class PWM
{

  public:
    PWM(GPIOIf *gpio,
        unsigned int frequency,
        float dutyCycle);

    ~PWM();

    void start();
    void stop();
    void setDutyCycle(float dutyCycle);

  private:

    struct timing
             {
        unsigned on;
        unsigned off;
    } m_timing;

    void runnable();

    std::thread m_thread;
    GPIOIf *m_gpio;
    unsigned int m_frequency;
    float m_dutyCycle;
    bool m_isRunning;
    unsigned int m_totalTime;


};
#endif // PWM_H
