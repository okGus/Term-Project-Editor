#include "Point.h"
#include <iostream>
#include <cmath>

Point::Point() : x(0), y(0)
{
}

Point::Point(int _x, int _y) {
    x = _x;
    y = _y;
}

int Point::get_x() const { return x; }
int Point::get_y() const { return y; }

void Point::set_x(int new_x) {
    x = new_x;
}

void Point::set_y(int new_y) {
    y = new_y;
}

void Point::display() {
    std::cout << "(" << x << "," << y << ")";
}

double Point::distance_(Point otherPoint) const {
    return std::sqrt(std::pow((otherPoint.x - x), 2) + std::pow((otherPoint.y - y), 2));
}

bool Point::operator==(Point secondPoint) const {
    return (secondPoint.x == x && secondPoint.y == y);
}