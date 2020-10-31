#ifndef POINT_
#define POINT_

class Point
{
private:
    int x{};
    int y{};

public:
    // x and y set to zero
    Point();
    // set _x and _y to private x and y
    Point(int _x, int _y);

    int get_x() const;
    int get_y() const;
    void set_x(int new_x);
    void set_y(int new_y);
    void display();
    double distance_(Point otherPoint) const;
    bool operator==(Point secondPoint) const;
};
#endif