#include "CommandPlus.h"

void CommandPlus::setCommand()
{
    ch = getch();
}

int CommandPlus::getCommand() const
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

std::string CommandPlus::getValue() const
{
    return value;
}

int CommandPlus::getYLocation() const
{
    return location.get_y();
}

int CommandPlus::getXLocation() const
{
    return location.get_x();
}