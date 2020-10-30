#include "Editor.h"

// NON-CLASS FUNCTIONS


Editor::Editor() {
}

Editor::Editor(std::string filename) {
    unsigned int lineCounter{1};
    std::fstream read_file;

    read_file.open(filename);

    if(read_file.fail()) {
        std::cerr << "Error opening file: " << filename << '\n';
        std::exit(EXIT_FAILURE);
        //throw("Error opening file");
    }
    while(!read_file.eof()) {
        std::string _line{};
        std::getline(read_file, _line);
        lineNumber.insert(lineCounter, _line);
        lineCounter++;
    }

    read_file.close();
}

void Editor::displayLines() {
    unsigned int i{1};
    const char EXIT{'q'};

    initscr();  // Start curses mode
    noecho();   // No echoing to screen
    raw();      // Prevents use of signals from ctl + c

    int ch { getch() };

    // Output text to window with printw() from filename
    for (; i < lineNumber.getLength() + 1; i++) {
        std::string ch { lineNumber.getEntry(i) };
        printw(ch.c_str());  
        printw("\n");
    }

    move(0,0);
    refresh();  // Update screen

    while((ch = getch()) != EXIT) {
        switch(ch) {
            case 'j':
                move(userPosition.get_y() + 1, userPosition.get_x());
                refresh();
                break;
        }
    }

    endwin();   // End curses mode
}

void Editor::moveDown() {
    
}