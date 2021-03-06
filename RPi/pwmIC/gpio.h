#ifndef JKB_GPIO_H
#define JKB_GPIO_H

#include <map>
#include <iostream>

class GPIOIf
{
	public:
	enum MODE {
      IN,
      OUT
    };
	 virtual void turnOn() = 0;
	 virtual void turnOff() = 0;
};

class GPIO : public GPIOIf
{
  public:
    

    GPIO(unsigned int pin,
         const MODE dir,
         bool inverted = false);
    ~GPIO();

    void turnOn();
    void turnOff();

  private:
    int openFD(const std::string path);
    int closeFD(int fd);
    int writeTo(int fd, const std::string &val);
    void writeToPath(std::string path, std::string val);

    std::string m_exportPath;
    std::string m_unExportPath;
    std::string m_valuePath;
    std::string m_directionPath;
    std::string m_pin;
    int m_ValueFD;
    MODE m_direction;
    std::map<int, std::string> m_fdMap;
    std::map<MODE, std::string> m_modeMap;

    bool m_inverted;

    std::string m_on;
    std::string m_off;
};
#endif
