/***********************************
 * Editor class interface
 *
 * @author Vikas Choudhary
 * @date   05/24/2023 
 **********************************/
#ifndef EDITOR_H
#define EDITOR_H

#include <string>
using std::string;

// Modes of editor(At a time one of these mode will be active)
enum class EditorMode {
    EDIT,
    COMMAND
};

class Editor {
private:
    string fileName;
    string fileContent;
    EditorMode currMode;

public:
    Editor();
    Editor(const string& fileName);
};

#endif