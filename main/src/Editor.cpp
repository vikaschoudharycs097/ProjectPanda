/************************************************
 * Implementation of Editor class functionality
 * 
 * @author Vikas Choudhary
 * @date   05/24/2023
 ***********************************************/

#include "Editor.h"
#include <unistd.h>
#include <termios.h>
#include <cctype>

Editor::Editor(): fileName(""), fileContent(""), currMode(EditorMode::COMMAND), editorConfig() {
}

Editor::Editor(const string& fileName): fileName(fileName), fileContent(""), 
        currMode(EditorMode::COMMAND), editorConfig() {
}

Editor::~Editor() {
}

// Read text from STDIN in raw mode
void Editor::editText(void) {
    char ch;

    // Read text
    while (read(STDIN_FILENO, &ch, 1) == 1 && ch != ESC) {
        write(STDOUT_FILENO, &ch, 1);
    }
}

// Invert the mode of editor
void Editor::invertMode(void) {
    if (EditorMode::EDIT == currMode) {
        currMode = EditorMode::COMMAND;
        editorConfig.setCursorToBottomLeft();
    } else {
        currMode = EditorMode::EDIT;
        editorConfig.setCursorToTopLeft();
    }
}

// Manages Editor's functionalities
void Editor::start(void) {
    bool exitEditor = false;

    // Enable raw mode
    editorConfig.enableRawMode();

    // Refresh editor screen
    refreshScreen();

    // Draw tildes
    drawTildes();

    // Testing: Update mode to Edit and call textEdit
    do {
        switch (currMode) {
            case EditorMode::EDIT:
                editText();
                break;
            case EditorMode::COMMAND:
                exitEditor = getCommand() == 'q';
                break;
        }

        invertMode();
    } while (!exitEditor);

    // Refresh editor screen
    refreshScreen();

    // Disable raw mode
    editorConfig.disableRawMode();
}

// Refresh the text editor screen
void Editor::refreshScreen(void) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

// Draw Tildes in first column
void Editor::drawTildes(void) {
    for (int i = 0, n = editorConfig.getWindowRows(); i < n; i++) {
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

// Get the command
char Editor::getCommand(void) {
    char ch;

    // Read command
    while (read(STDIN_FILENO, &ch, 1) == 1 && ch != ESC) {
        write(STDOUT_FILENO, &ch, 1);
        if (ch == 'q') {
            break;
        }
    }
    
    return ch;
}