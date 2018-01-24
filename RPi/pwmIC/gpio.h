#ifndef GPIO_H
#define GPIO_H

#include <map>
#include <iostream>

class GPIOIf
{
	public:
	 virtual void turnOn() = 0;
	 virtual void turnOff() = 0;
};

class GPIO : public GPIOIf
{
  public:
    enum MODE {
      IN,
      OUT
    };

    GPIO(unsigned int pin, const MODE dir);
    ~GPIO();

    void turnOn();
    void turnOff();

private:
    std::string m_exportPath;
    std::string m_unExportPath;
    std::string m_valuePath;
    std::string m_directionPath;
    std::string m_pin;
    int m_ValueFD;
    MODE m_direction;
    std::map<int, std::string> m_fdMap;
    std::map<MODE, std::string> m_modeMap;
#endif
