#ifndef EDITOR_
#define EDITOR_

#include "Point.h"
#include "LinkedList.h"
#include <string>
#include <fstream>
#include <iostream>

// Linux based because can't use Windows.h
#include <ncurses.h>

class Editor
{
private:
    LinkedList<std::string> lineNumber;
    Point userPosition;

public:
    Editor();
    Editor(std::string filename);
    void displayLines();
    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();
    void run();
};
#endif