#ifndef EDITOR_
#define EDITOR_

#include "Point.h"
#include "LinkedList.h"
#include <string>
#include <fstream>
#include <iostream>
//#include <Windows.h>

class Editor {
private:
    LinkedList<std::string> lineNumber;
    Point userPosition;
public:
    Editor();
    Editor(std::string filename);
    void displayLines();
};
#endif