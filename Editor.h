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
    LinkedStack<CommandPlus> undoStack;
    Point userPosition;
    CommandPlus cmd;

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