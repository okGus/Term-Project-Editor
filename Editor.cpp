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
    unsigned int count{}; // Keeps track of case 'dd'
    CommandPlus cmd;

    initscr(); // Start curses mode
    noecho();  // No echoing to screen
    raw();     // Prevents use of signals from ctl + c

    int ch{cmd.getCommand()};

    // Output text to window with printw() from filename
    display();

    move(0, 0);
    refresh(); // Update screen

    while ((ch = getch()) != QUIT && ch != ESCAPE)
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
        case 'u': // undo
            undo_();
            clear();
            display();
            break;
        case 'i': // Insert
            insert_();
            count = 0;
            break;
        default:
            count = 0;
            break;
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
    // Was
    /* 
    if (userPosition.get_x() < lineNumber.getEntry(userPosition.get_y() + 1).length())
    {
        userPosition.set_x(userPosition.get_x() + 1);
    }
     */
    if (userPosition.get_x() < lineNumber.getEntry(userPosition.get_y() + 1).length())
    {
        userPosition.set_x(userPosition.get_x() + 1);
    }

    move(userPosition.get_y(), userPosition.get_x());
}

void Editor::deleteChar()
{
    if (lineNumber.getEntry(userPosition.get_y() + 1).length() > 0)
    {
        CommandPlus cmd;
        // save value and location then push to stack
        cmd.setValue(lineNumber.getEntry(userPosition.get_y() + 1).substr(userPosition.get_x(), 1));
        cmd.setLocation(userPosition);
        undoStack.push(cmd);
    }
    // Push char, then replace new string
    lineNumber.replace(userPosition.get_y() + 1, lineNumber.getEntry(userPosition.get_y() + 1).erase(userPosition.get_x(), 1));
    // Reset position
    if (userPosition.get_x() > 0)
        userPosition.set_x(userPosition.get_x() - 1);
}

void Editor::deleteLine()
{
    bool removed = false;
    CommandPlus cmd;

    // save value and location then push to stack
    cmd.setValue(lineNumber.getEntry(userPosition.get_y() + 1));
    cmd.setLocation(userPosition);

    // Push line, then remove it
    undoStack.push(cmd);

    // This prevents the last node from being deleted
    // instead replacing it with an empty string
    if (lineNumber.getLength() == 1)
    {
        lineNumber.replace(1, "");
        removed = true;
    }

    // When deleting a line, the Y-coord should be decremented so to prevent
    // the cursor from being on an empty line
    if (userPosition.get_y() > 0 && !removed)
    {
        lineNumber.remove(userPosition.get_y() + 1);
        userPosition.set_y(userPosition.get_y() - 1);
        removed = true;
    }

    if (!removed)
        lineNumber.remove(userPosition.get_y() + 1);

    // If the x position is greater than the length of the new line
    // then put the cursor position to the last char of the line
    // If the line is empty (a "" string) then set 'x' coord to 0
    if (lineNumber.getEntry(userPosition.get_y() + 1).length() > 0)
        userPosition.set_x(lineNumber.getEntry(userPosition.get_y() + 1).length() - 1);
    else
        userPosition.set_x(0);
}
// insert should be by char, with getch(),
void Editor::insert_()
{
    CommandPlus tempCommand;
    tempCommand.setValue(lineNumber.getEntry(userPosition.get_y() + 1));
    undoStack.push(tempCommand);

    // Set and move cursor 1+
    // userPosition.set_x(userPosition.get_x() + 1);
    // move(userPosition.get_y(), userPosition.get_x());

    while (true)
    {
        int _char = getch();

        if (_char == ESCAPE)
        {
            // Reset cursor
            // userPosition.set_x(userPosition.get_x() - 1);
            // move(userPosition.get_y(), userPosition.get_x());
            break;
        }

        // WIP
        if (_char == '\n')
        {
            lineNumber.insert(userPosition.get_y() + 2, " ");
            userPosition.set_x(0);
            userPosition.set_y(userPosition.get_y() + 2);
            move(userPosition.get_y(), userPosition.get_x());
            // Update display
            refresh();
            clear();
            display();
            continue;
        }

        // Place user's inputed character to modify string in y coordinate
        lineNumber.replace(userPosition.get_y() + 1, lineNumber.getEntry(userPosition.get_y() + 1).insert(userPosition.get_x(), 1, _char));

        // Update display
        clear();
        display();

        // Push new modified line to stack
        tempCommand.setValue(lineNumber.getEntry(userPosition.get_y() + 1));
        undoStack.push(tempCommand);

        // Set and move cursor 1+ after modified string
        userPosition.set_x(userPosition.get_x() + 1);
        move(userPosition.get_y(), userPosition.get_x());
    }

    // Reset cursor
    // userPosition.set_x(userPosition.get_x() - 1);
    // move(userPosition.get_y(), userPosition.get_x());
}

void Editor::undo_()
{
    CommandPlus tempCmd;
    if (!undoStack.isEmpty())
    {
        tempCmd = undoStack.peek();
        undoStack.pop();

        // If we are undoing a string deleting then we insert it back
        if (tempCmd.getValue().length() > 1 || tempCmd.getValue() == "")
            lineNumber.insert(tempCmd.getYLocation() + 1, tempCmd.getValue());

        // Else, we are restoring a character, which requires the string
        // to be replaced with the character in the exact place it originally was
        else
        {
            lineNumber.replace(tempCmd.getYLocation() + 1, lineNumber.getEntry(tempCmd.getYLocation() + 1).insert(tempCmd.getXLocation(), tempCmd.getValue()));
            // This increments the x position as you are undoing as long as the length
            // of the line is longer than the x position
            // We only want to incremetn 'x' if we're undoing chars, which is why it's inside this else statement
            if (userPosition.get_x() < lineNumber.getEntry(userPosition.get_y() + 1).length() - 1)
                userPosition.set_x(userPosition.get_x() + 1);
        }

        // This stops the x cursor from going out of bounds
        if (userPosition.get_x() >= lineNumber.getEntry(userPosition.get_y() + 1).length())
            userPosition.set_x(lineNumber.getEntry(userPosition.get_y() + 1).length() - 1);
        // This stops x-coor from going negative
        if (userPosition.get_x() < 0)
            userPosition.set_x(0);
    }
}