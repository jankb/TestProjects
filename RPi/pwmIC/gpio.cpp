#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include "gpio.h"



GPIO::GPIO(unsigned int pin, const MODE dir, bool inverted)
      : m_pin(std::to_string(pin)),
      m_exportPath("/sys/class/gpio/export"),
      m_unExportPath("/sys/class/gpio/unexport"),
      m_valuePath("/sys/class/gpio/"),
      m_direction(dir),
      m_ValueFD(-1),
      m_inverted(inverted)
{
  m_modeMap[IN] = "in"; 
  m_modeMap[OUT] = "out"; 
  m_fdMap[-1] = "PATH NOT SET";
  m_valuePath += "gpio"+m_pin+"/value";
  m_directionPath = "/sys/class/gpio/gpio"+m_pin+"/direction";
  writeToPath(m_exportPath, m_pin);
  writeToPath(m_directionPath, m_modeMap[m_direction]);
  m_ValueFD = openFD(m_valuePath);

  if (m_inverted)
  {
      m_on  = '0';
      m_off = '1';
  }
  else
  {
      m_on  = '1';
      m_off = '0';
  }
}


GPIO::~GPIO()
{
  writeToPath(m_unExportPath, m_pin);
  closeFD(m_ValueFD);
}

void GPIO::turnOn()
{
  writeTo(m_ValueFD, m_on);
}

void GPIO::turnOff()
{
  writeTo(m_ValueFD, m_off);
}


int GPIO::openFD(const std::string path)
{
  int fd = open(path.c_str(), O_WRONLY);
  if (fd  == -1)
  {
    int err = errno;
    std::cerr << "Error " << std::strerror(err) << " opening " << path.c_str() << std::endl;
  } 
  else
  {
    m_fdMap[fd] = path;
  }
  return fd;
}

int GPIO::closeFD(int fd)
{
  int res = close(fd);
  if (res  == -1)
  {
    int err = errno;
    std::cerr << "Error " << std::strerror(err) << " closing " << m_fdMap[fd] << std::endl;
  } 
  return res;
}

int GPIO::writeTo(int fd, const std::string &val)
{
    const char* value = val.c_str();
    ssize_t res = write(fd, value, sizeof(value));
    if (res == -1)
    {
        int err = errno;
        std::cerr << "Error " << std::strerror(err) << " writing " << value << " to " << m_fdMap[fd] << std::endl;
    }
    else
    {
    //    std::cout << "Writing " << value << " to " << m_fdMap[fd] << std::endl;
    }
    return res;
}


void GPIO::writeToPath(std::string path, std::string val)
{
  int fd = openFD(path);
  if (fd != -1)
  {
    writeTo(fd, val);
    closeFD(fd);
  }
}

