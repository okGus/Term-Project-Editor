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

void Editor::run()
{
    unsigned int i{1};
    const char QUIT{'q'};
    const int ESCAPE{27};
    unsigned int count{}; // Keeps track of case 'dd'

    initscr(); // Start curses mode
    noecho();  // No echoing to screen
    raw();     // Prevents use of signals from ctl + c

    int ch{cmd.getCommand()};

    // Output text to window with printw() from filename
    display();

    move(0, 0);
    refresh(); // Update screen

    while ((ch = getch()) != QUIT)
    {
        switch (ch)
        {
        case 'j':
            //case KEY_DOWN:
            moveDown();
            refresh();
            count = 0;
            break;
        case 'k':
            //case KEY_UP:
            moveUp();
            refresh();
            count = 0;
            break;
        case 'h':
            //case KEY_LEFT:
            moveLeft();
            refresh();
            count = 0;
            break;
        case 'l':
            //case KEY_RIGHT:
            moveRight();
            refresh();
            count = 0;
            break;
        case 'x': // delete char
            deleteChar();
            clear();
            display();
            move(userPosition.get_y(), userPosition.get_x());
            count = 0;
            break;
        case 'd': // delete line 'dd'
            count++;
            if (count == 2)
            {
                deleteLine();
                clear();
                display();
                move(userPosition.get_y(), userPosition.get_x());
                count = 0;
            }
            break;
        case 'i': // Insert
            echo();
            insert_();
            count = 0;
            break;
        case ESCAPE:
            std::exit(EXIT_FAILURE);
        }
    }

    endwin(); // End curses mode
}

void Editor::display()
{
    // Display for ncurses
    unsigned int i{1};
    for (; i < lineNumber.getLength() + 1; i++)
    {
        std::string ch{lineNumber.getEntry(i)};
        printw(ch.c_str());
        printw("\n");
    }
}

void Editor::displayLine()
{
    // This play for normal function (non-ncurses)
    unsigned int i{1};
    for (; i < lineNumber.getLength() + 1; i++)
    {
        std::cout << lineNumber.getEntry(i);
        std::cout << '\n';
    }
}

void Editor::moveDown()
{
    if (userPosition.get_y() < lineNumber.getLength() - 1)
    {
        // x-coordinate has to be within bounds
        if (userPosition.get_x() >= lineNumber.getEntry(userPosition.get_y() + 2).length())
        {
            userPosition.set_x(lineNumber.getEntry(userPosition.get_y() + 2).length() - 1);
        }

        userPosition.set_y(userPosition.get_y() + 1);
        move(userPosition.get_y(), userPosition.get_x());
    }
}

void Editor::moveUp()
{
    if (userPosition.get_y() > 0)
    {
        // x-coordinate has to be within bounds
        if (userPosition.get_x() >= lineNumber.getEntry(userPosition.get_y()).length())
        {
            userPosition.set_x(lineNumber.getEntry(userPosition.get_y()).length() - 1);
        }

        userPosition.set_y(userPosition.get_y() - 1);
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

void Editor::deleteChar()
{
    // save value and location then push to stack
    cmd.setValue(lineNumber.getEntry(userPosition.get_y() + 1).substr(userPosition.get_x(), 1));
    cmd.setLocation(userPosition);
    // Push char, then replace new string
    undoStack.push(cmd);
    lineNumber.replace(userPosition.get_y() + 1, lineNumber.getEntry(userPosition.get_y() + 1).erase(userPosition.get_x(), 1));
    // Reset position
    if (userPosition.get_x() > 0)
        userPosition.set_x(userPosition.get_x() - 1);
}

void Editor::deleteLine()
{
    // save value and location then push to stack
    cmd.setValue(lineNumber.getEntry(userPosition.get_y() + 1));
    cmd.setLocation(userPosition);
    // Push line, then remove it
    undoStack.push(cmd);
    lineNumber.remove(userPosition.get_y() + 1);
}

void Editor::insert_()
{
    bool insertMode{true};
    while (insertMode)
    {
        // Set and move cursor 1+
        userPosition.set_x(userPosition.get_x() + 1);
        move(userPosition.get_y(), userPosition.get_x());

        // Get user input
        char userInput[256];
        getstr(userInput);

        // Append to last in position y
        lineNumber.replace(userPosition.get_y() + 1, lineNumber.getEntry(userPosition.get_y() + 1).append(userInput));
        // Fix and move to new position
        userPosition.set_x(lineNumber.getEntry(userPosition.get_y() + 1).length() - 1);
        move(userPosition.get_y(), userPosition.get_x());
        noecho();
        if (getch() == 27)
        {
            insertMode = false;
        }
    }
}

void Editor::undo_()
{
    
}