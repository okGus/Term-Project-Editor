#ifndef EDITOR_
#define EDITOR_

#include "Point.h"
#include "LinkedList.h"
#include <string>

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