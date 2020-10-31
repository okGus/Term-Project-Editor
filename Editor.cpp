#include "Editor.h"

// NON-CLASS FUNCTIONS

Editor::Editor()
{
}

Editor::Editor(std::string filename)
{
    unsigned int lineCounter{1};
    std::fstream read_file;

    read_file.open(filename);

    if (read_file.fail())
    {
        std::cerr << "Error opening file: " << filename << '\n';
        std::exit(EXIT_FAILURE);
        //throw("Error opening file");
    }
    while (!read_file.eof())
    {
        std::string _line{};
        std::getline(read_file, _line);
        lineNumber.insert(lineCounter, _line);
        lineCounter++;
    }

    read_file.close();
}

void Editor::displayLines()
{
    unsigned int i{1};
    const char QUIT{'q'};

    initscr(); // Start curses mode
    noecho();  // No echoing to screen
    raw();     // Prevents use of signals from ctl + c

    int ch{getch()};

    // Output text to window with printw() from filename
    for (; i < lineNumber.getLength() + 1; i++)
    {
        std::string ch{lineNumber.getEntry(i)};
        printw(ch.c_str());
        printw("\n");
    }

    move(0, 0);
    refresh(); // Update screen

    while ((ch = getch()) != QUIT)
    {
        switch (ch)
        {
        case 'j':
            moveDown();
            refresh();
            break;
        case 'k':
            moveUp();
            refresh();
            break;
        case 'h':
            moveLeft();
            refresh();
            break;
        case 'l':
            moveRight();
            refresh();
            break;
        }
    }

    endwin(); // End curses mode
}

void Editor::moveDown()
{
    if (userPosition.get_y() < lineNumber.getLength() - 1)
    {
        // x-coordinate has to be within bounds
        if (userPosition.get_x() < lineNumber.getEntry(userPosition.get_y() + 1).length())
        {
            userPosition.set_y(userPosition.get_y() + 1);
        }

        move(userPosition.get_y(), userPosition.get_x());
    }
}

void Editor::moveUp()
{
    if (userPosition.get_y() > 0)
    {
        // x-coordinate has to be within bounds
        if (userPosition.get_x() < lineNumber.getEntry(userPosition.get_y()).length())
        {
            userPosition.set_y(userPosition.get_y() - 1);
        }

        move(userPosition.get_y(), userPosition.get_x());
    }
}

void Editor::moveLeft()
{
    // If within bounds
    if (userPosition.get_x() > 0)
    {
        userPosition.set_x(userPosition.get_x() - 1);
    }

    move(userPosition.get_y(), userPosition.get_x());
}

void Editor::moveRight()
{
    // If within bounds
    if (userPosition.get_x() < lineNumber.getEntry(userPosition.get_y() + 1).length() - 1)
    {
        userPosition.set_x(userPosition.get_x() + 1);
    }

    move(userPosition.get_y(), userPosition.get_x());
}