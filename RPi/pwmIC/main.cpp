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
      m_direction(dir),
      m_ValueFD(-1)
  {
    m_modeMap[IN] = "in"; 
    m_modeMap[OUT] = "out"; 
    m_valuePath += "gpio"+m_pin+"/value";
    m_directionPath = "/sys/class/gpio/gpio"+m_pin+"/direction";
    writeToPath(m_exportPath, m_pin);
    writeToPath(m_directionPath, m_modeMap[m_direction]);
    m_ValueFD = openFD(m_valuePath);
  }


    ~GPIO()
    {
      writeToPath(m_unExportPath, m_pin);
      closeFD(m_ValueFD);
    }

    void turnOn()
    {
      writeTo(m_ValueFD, "1");
    }

    void turnOff()
    {
      writeTo(m_ValueFD, "0");
    }

  private:
    std::map<MODE, std::string> m_modeMap;

    int openFD(const std::string path)
    {
      int fd = open(path.c_str(), O_WRONLY);
      if (fd  == -1)
      {
        int err = errno;
        printf("Error %d opening %s.\n", err, path.c_str());
      } 
      else
      {
      m_fdMap[fd] = path;
      }
      return fd;
    }

    int closeFD(int fd)
    {
      int res = close(fd);
      if (res  == -1)
      {
        int err = errno;
        printf("Error %d closing %s.\n", err, m_fdMap[fd]);
      } 
      return res;
    }

    int writeTo(int fd, const std::string &val)
    {
      const char* value = val.c_str();
      printf("Writing %s to %s\n", value, (m_fdMap[fd]).c_str());
      ssize_t res = write(fd, value, sizeof(value));
      if (res == -1)
      {
        int err = errno;
        printf("Error %d writing %s to fd %d, %s.\n", err, value, fd, m_fdMap[fd]);
      }
      return res;
    }


    void writeToPath(std::string path, std::string val)
    {
      int fd = openFD(path);
      if (fd != -1)
      {
        writeTo(fd, val);
        closeFD(fd);
      }
    }

    std::string m_exportPath;
    std::string m_unExportPath;
    std::string m_valuePath;
    std::string m_directionPath;
    std::string m_pin;
    int m_ValueFD;
    MODE m_direction;
    std::map<int, std::string> m_fdMap;
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
