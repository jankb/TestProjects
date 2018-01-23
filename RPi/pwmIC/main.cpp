#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <cstdio>

#include <map>

class GPIO
{
  public:
    enum MODE {
      IN,
      OUT
    };

    GPIO(unsigned int pin, const MODE dir) 
      : m_pin(std::to_string(pin)),
      m_exportPath("/sys/class/gpio/export"),
      m_unExportPath("/sys/class/gpio/unexport"),
      m_valuePath("/sys/class/gpio/"),
      m_direction(dir)
  {
    m_modeMap[IN] = "in"; 
    m_modeMap[OUT] = "out"; 
    m_valuePath += "gpio"+m_pin+"/value";
    m_directionPath = "/sys/class/gpio/gpio"+m_pin+"/direction";
    writeToPath(m_exportPath, m_pin);
    writeToPath(m_directionPath, m_modeMap[m_direction]);
  }


    ~GPIO()
    {
      writeToPath(m_unExportPath, m_pin);
    }

   void turnOn()
    {
      writeToPath(m_valuePath, "1");
    }

   void turnOff()
    {
      writeToPath(m_valuePath, "0");
    }

  private:
    std::map<MODE, std::string> m_modeMap;

    void writeToPath(std::string path, std::string val)
    {
      std::cout << path <<" " << val << std::endl;
      int fd = open(path.c_str(), O_WRONLY);
      if (fd == -1)
      {
        int err = errno;
        printf("Error %d opening %s.\n", err, path.c_str());
        return;
      } else
      {
        const char* pin = val.c_str();
        ssize_t res = write(fd, pin, sizeof(pin));
        if (res == -1)
        {
          int err = errno;
          printf("Error %d writing %d to device %s.\n", err, pin, path.c_str());
          return;
        }
      }
    }

    std::string m_exportPath;
    std::string m_unExportPath;
    std::string m_valuePath;
    std::string m_directionPath;
    std::string m_pin;
    MODE m_direction;
};


int main()
{
  std::cout << "Starting." << std::endl;
  GPIO gpio(13,GPIO::OUT);
  gpio.turnOn();
  gpio.turnOff();
  return 0;
}
