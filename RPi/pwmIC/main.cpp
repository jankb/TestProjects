#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <cstdio>

class GPIO
{
  public:
    GPIO(unsigned int pin) 
      : m_pin(std::to_string(pin)),
        m_exportPath("/sys/class/gpio/export"),
        m_unExportPath("/sys/class/gpio/unexport")
    {
      
      writeToPath(m_exportPath, m_pin);
    }
    ~GPIO()
    {
      writeToPath(m_unExportPath, m_pin);
    }

  private:


    void writeToPath(std::string path, std::string val)
    {
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
    std::string m_pin;
};


int main()
{
  std::cout << "Starting." << std::endl;
  GPIO gpio(17);
	return 0;
}
