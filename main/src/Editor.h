/***********************************
 * Editor class interface
 *
 * @author Vikas Choudhary
 * @date   05/24/2023 
 **********************************/
#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <termios.h>
using std::string;

// Modes of editor(At a time one of these mode will be active)
enum class EditorMode {
    EDIT,
    COMMAND
};

class Editor {
private:
    // Private data members
    string fileName;
    string fileContent;
    EditorMode currMode;
    struct termios canonicalMode;
    struct termios rawMode;

    // Private member functions
    void editText(void);
    void enableRawMode(void);
    void disableRawMode(void);
    void setRawMode(void);

    // Static Constants
    const char ESC = (char) 27;

public:
    Editor();
    Editor(const string& fileName);
    ~Editor();
    void updateMode(const EditorMode newMode);
    void start();  // Manages Editor's functionalities
};

#endif