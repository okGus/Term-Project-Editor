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
    int getCommand();
    void setCommand();
    void setValue(const std::string &_value);
    void setLocation(const Point &_location);
};