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

    // Editor operations
    void editText(void);
    void invertMode(void);
    char getCommand(void);
    int readKeypress(void);
    void refreshScreen(void);
    void renderScreen(int startRow = 0);

    // Character Operations
    void saveText(void);
    void insertChar(int ch);
    void deleteChar(void);
    void deletePreviousChar(void);
    void handleNewline(int ch);
    void handleIsGraph(int ch);
    void handleHorizontalTab(int ch);

public:
    Editor();
    Editor(const string& fileName);
    ~Editor();
    void start();  // Manages Editor's functionalities
};

#endif // EDITOR_H