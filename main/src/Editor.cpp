/************************************************
 * Implementation of Editor class functionality
 * 
 * @author Vikas Choudhary
 * @date   05/24/2023
 ***********************************************/

#include "Editor.h"
#include <unistd.h>
#include <termios.h>
#include <fstream>
#include <cctype>
#include <iostream>
using std::fstream;
using std::cout;

Editor::Editor(): fileName(""), currMode(EditorMode::COMMAND), editorConfig() {
}

Editor::Editor(const string& fileName): fileName(fileName), currMode(EditorMode::COMMAND), editorConfig() {
    if (fileName != "") {
        fstream file(fileName, fstream::in | fstream::out);
        if (file.is_open()) {
            string line;
            while (file) {
                getline(file, line);
                textRows.push_back(line);
            }
        } else {
            cout << "Not opened\n";
        }
    }
}

Editor::~Editor() {
}

// Read text from STDIN in raw mode
void Editor::editText(void) {
    int ch = 0;

    // Read text
    while ((ch = readKeypress()) != ESC) {
        switch (ch) {
            case ARROW_DOWN:
            case ARROW_RIGHT:
            case ARROW_LEFT:
            case ARROW_UP:
                editorConfig.updateCurrentPosition(ch);
                break;
        }
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
    // No Tildes in first row
    string tildes = "\r\n";

    // Draw Tildes from [2, rows)
    for (int i = 1, n = editorConfig.getWindowRows() - 1; i < n; i++) {
        tildes += "~\r\n";
    }

    // Write tildes in single syscall command
    write(STDOUT_FILENO, tildes.c_str(), tildes.size());
}

// Get the command
char Editor::getCommand(void) {
    char ch = 0;

    // Read command
    while ((ch = readKeypress()) != ESC && ch != 'q') {
    }
    
    return ch;
}

// Read key press
int Editor::readKeypress(void) {
    char ch;
    read(STDIN_FILENO, &ch, 1);

    if (ch == ESC) {
        // Read remaining two bytes of escape sequence
        char seq[3];
        if (read(STDIN_FILENO, seq, 2) == 2) {
            if (seq[0] == '[') {
                switch (seq[1]) {
                    case 'A': return ARROW_UP;
                    case 'B': return ARROW_DOWN;
                    case 'C': return ARROW_RIGHT;
                    case 'D': return ARROW_LEFT;
                }
            }
        } 
    }

    return ch;
}