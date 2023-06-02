/************************************************
 * Implementation of Editor class functionality
 * 
 * @author Vikas Choudhary
 * @date   05/24/2023
 ***********************************************/

#include "Editor.h"
#include <unistd.h>
#include <termios.h>

Editor::Editor(): fileName(""), fileContent(""), currMode(EditorMode::COMMAND) {
}

Editor::Editor(const string& fileName): fileName(fileName), fileContent(""), 
        currMode(EditorMode::COMMAND) {
}

Editor::~Editor() {
}

// Read text from STDIN in raw mode
void Editor::editText(void) {
    char ch;
    enableRawMode();
    while (read(STDIN_FILENO, &ch, 1) == 1 && ch != ESC);
}

// Update the mode of editor
void Editor::updateMode(const EditorMode newMode) {
    currMode = newMode;
}

// Manages Editor's functionalities
void Editor::start(void) {
    // Testing: Update mode to Edit and call textEdit
    updateMode(EditorMode::EDIT);
    editText();
}

// Enable Raw mode
void Editor::enableRawMode(void) {
    struct termios mode;
    tcgetattr(STDIN_FILENO, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &mode);
}