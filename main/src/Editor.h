/***********************************
 * Editor class interface
 *
 * @author Vikas Choudhary
 * @date   05/24/2023 
 **********************************/
#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <vector>
#include <termios.h>
#include "EditorConfig.h"
using std::string;
using std::vector;

// Modes of editor(At a time one of these mode will be active)
enum class EditorMode {
    EDIT,
    COMMAND
};

class Editor {
private:
    // Private data members
    string fileName;
    EditorMode currMode;
    EditorConfig editorConfig;
    vector<string> textRows;

    // Private member functions
    void editText(void);
    void refreshScreen(void);
    void drawTildes(void);
    void invertMode(void);
    char getCommand(void);
    int readKeypress(void);
    void insertChar(char ch, size_t row, size_t col);

    // Static Constants
    const char ESC = (char) 27;

public:
    Editor();
    Editor(const string& fileName);
    ~Editor();
    void start();  // Manages Editor's functionalities
};

#endif