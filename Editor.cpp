#include "Editor.h"

//#include "Windows.h"
// NON-CLASS FUNCTIONS
void displayWindow() {
    Display *dpy = XOpenDisplay(0);
    assert(dpy);

    int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
    int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

    // Create window
    Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0,
                                    200, 100, 0, blackColor, blackColor);

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
}

void Editor::displayLines() {
    unsigned int i{1};
    for (; i < lineNumber.getLength() + 1; i++) {
        std::cout << lineNumber.getEntry(i);
        std::cout << '\n';
    }
}