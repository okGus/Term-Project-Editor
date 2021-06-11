#include "Point.h"
#include <string>
#include <ncurses.h>

class CommandPlus
{
private:
    int ch;
    Point location;
    std::string value;

public:
    int getCommand() const;
    void setCommand();
    void setValue(const std::string &_value);
    std::string getValue() const;
    void setLocation(const Point &_location);
    int getYLocation() const;
    int getXLocation() const;
};