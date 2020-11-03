#ifndef EDITOR_
#define EDITOR_

#include "Point.h"
#include "LinkedList.h"
#include "LinkedStack.h"
#include <string>
#include <fstream>
#include <iostream>

// Linux based because can't use Windows.h
#include <ncurses.h>

class Editor
{
private:
    LinkedList<std::string> lineNumber;
    LinkedStack<std::string> undoStack;
    Point userPosition;

public:
    Editor();
    Editor(std::string filename);
    void display();
    void displayLine();
    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();
    void deleteChar();
    void deleteLine();
    void run();
};
#endif