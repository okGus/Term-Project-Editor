#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Editor.h"

int main()
{
    std::string filename("test.txt");
    Editor miniEditor(filename);
    miniEditor.run();
    //miniEditor.displayLine();
    return 0;
}

/*
// Handles exception thrown from constructor
    try {
        miniVim = new Editor(filename);
    } catch (const char *e) {
        std::cerr << "Stack exception: " << e << "\n";
    }
    miniVim->displayLines();
*/