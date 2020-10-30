#ifndef EDITOR_
#define EDITOR_

#include "Point.h"
#include "LinkedList.h"
#include <string>
#include <fstream>
#include <iostream>

// Linux based because can't use Windows.h
#include <ncurses.h>
//#include <X11/Xlib.h> // For Xlib programs
//#include <assert.h>
//#include <unistd.h>   // So we get the profile for 10 seconds


class Editor {
private:
    LinkedList<std::string> lineNumber;
    Point userPosition;
public:
    Editor();
    Editor(std::string filename);
    void displayLines();
    void moveDown();
};
#endif