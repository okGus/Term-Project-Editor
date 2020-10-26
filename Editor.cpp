#include "Editor.h"

// NON-CLASS FUNCTIONS
void displayWindow() {
    Display *dpy{XOpenDisplay(0)};
    int screen{DefaultScreen(dpy)};
    int depth{DefaultDepth(dpy,screen)};
    Visual *visual{DefaultVisual(dpy,screen)};
    XSetWindowAttributes attributes;
    Cursor cursor_shape{XCreateFontCursor(dpy, 132)};

    assert(dpy);
    attributes.background_pixel = XWhitePixel(dpy,screen);

    // Create window
    Window w = XCreateWindow(dpy, XRootWindow(dpy,screen), 200, 200, 350, 
            200, 5, depth, InputOutput, visual, CWBackPixel, &attributes);
    
    XDefineCursor(dpy,w,cursor_shape);

    // Show window
    XMapWindow(dpy, w);
    XFlush(dpy);

    sleep(10);
}


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

    displayWindow();
}

void Editor::displayLines() {
    unsigned int i{1};
    for (; i < lineNumber.getLength() + 1; i++) {
        std::cout << lineNumber.getEntry(i);
        std::cout << '\n';
    }
}