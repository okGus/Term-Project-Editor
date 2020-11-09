#ifndef EDITOR_
#define EDITOR_

#include "Point.h"
#include "LinkedList.h"
#include "LinkedStack.h"
#include <string>
#include <fstream>
#include <iostream>
#include "CommandPlus.h"

// Linux based because can't use Windows.h
#include <ncurses.h>

class Editor
{
private:
    LinkedList<std::string> lineNumber;
    LinkedStack<class CommandPlus> undoStack;
    Point userPosition;
    const char QUIT{'q'};
    const int ESCAPE{27};
    const int ENTER{13};

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
    void insert_();
    void undo_();
    void run();
};
#endif