#include "CommandPlus.h"

void CommandPlus::setCommand()
{
    ch = getch();
}

int CommandPlus::getCommand()
{
    return ch;
}

void CommandPlus::setLocation(const Point &_location)
{
    location = _location;
}

void CommandPlus::setValue(const std::string &_value)
{
    value = _value;
}