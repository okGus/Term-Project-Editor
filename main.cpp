#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Editor.h"

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        std::cerr << "argc is less than 1.\n";
        return -1;
    }

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