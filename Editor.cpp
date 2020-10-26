#include "Editor.h"

//#include "Windows.h"
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
    for (; i < lineNumber.getLength() + 1; i++) {
        std::cout << lineNumber.getEntry(i);
        std::cout << '\n';
    }
}