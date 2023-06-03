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
    tcgetattr(STDIN_FILENO, &canonicalMode);
    setRawMode();
}

Editor::Editor(const string& fileName): fileName(fileName), fileContent(""), 
        currMode(EditorMode::COMMAND) {
    tcgetattr(STDIN_FILENO, &canonicalMode);
    setRawMode();
}

Editor::~Editor() {
}

// Read text from STDIN in raw mode
void Editor::editText(void) {
    char ch;

    // Enable Raw mode
    enableRawMode();

    // Read text
    while (read(STDIN_FILENO, &ch, 1) == 1 && ch != ESC);

    // Disable Raw mode
    disableRawMode();
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
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawMode);
}

// Disable Raw or Enable Canonical mode
void Editor::disableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &canonicalMode);
}

// Set Raw mode
void Editor::setRawMode(void) {
    rawMode = canonicalMode;
    rawMode.c_lflag &= ~(ECHO | ICANON);
}