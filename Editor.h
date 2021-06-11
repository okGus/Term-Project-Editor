#ifndef EDITOR_
#define EDITOR_

#include "Point.h"
#include "LinkedList.h"
#include "LinkedStack.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "CommandPlus.h"

// Linux based because can't use Windows.h
#include <ncurses.h>

class Editor
{
private:
    LinkedList<std::string> lineNumber;
    LinkedStack<class CommandPlus> undoStack;
    Point userPosition;
    std::string textFile;
    std::vector<std::string> keywords;
    const char QUIT{'q'};
    const int ESCAPE{27};
    const int ENTER{10};
    bool insertMode{false};
    WINDOW *win;
    int height, width, startx, starty;

public:
    Editor();
    Editor(std::string filename);
    Editor(std::string filename, std::string keywordFile);
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