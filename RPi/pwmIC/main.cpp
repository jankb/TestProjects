#include <iostream>
#include <signal.h>
#include "gpio.h"
#include "pwm.h"

static bool isRunning = true;

void sigTermHandler(int param)
{
    std::cout << "SIGTERM caught, shutting down." << std::endl;
    isRunning = false;
}

int main()
{
  std::cout << "Starting." << std::endl;

  signal(SIGINT, sigTermHandler);

  GPIO *green = new GPIO(13,GPIO::OUT, true);
  GPIO *blue = new GPIO(18,GPIO::OUT, true);
  PWM pwm_g(green, 50, 0.20);
  PWM pwm_b(blue, 50, 0.20);

  pwm_g.start();
  pwm_b.start();

  while (isRunning)
  {
      for (float dc = 0.01; dc <= 0.99; dc += 0.01)
      {
          pwm_g.setDutyCycle(dc);
          pwm_b.setDutyCycle(dc*0.10);
          std::this_thread::sleep_for(std::chrono::milliseconds(20));
      }
      for (float dc = 0.96; dc >= 0.01; dc -= 0.01)
      {
          pwm_g.setDutyCycle(dc);
          pwm_b.setDutyCycle(dc*0.10);
          std::this_thread::sleep_for(std::chrono::milliseconds(20));
      }

  }

  pwm_g.stop();
  pwm_b.stop();
  delete green;
  delete blue;

  std::cout << "Stopped." << std::endl;
  return 0;
}
