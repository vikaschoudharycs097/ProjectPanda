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
#include <vector>
#include <string>
#include <algorithm>
using std::fstream;
using std::max;
using std::vector;
using std::string;

Editor::Editor(): fileName(""), currMode(EditorMode::COMMAND), editorConfig(), textRows{""} {
}

Editor::Editor(const string& fileName): fileName(fileName), currMode(EditorMode::COMMAND), editorConfig() {
    size_t maxColumns = 0;
    if (fileName != "") {
        string line;
        fstream file(fileName, fstream::in | fstream::app);
        while (!file.eof()) {
            getline(file, line);
            textRows.push_back(line);
            maxColumns = max(maxColumns, line.length());
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
                editorConfig.updateCurrentPosition(ch, textRows);
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
    string tildes = "";
    int n = textRows.size();
    for (int i = 0; i < n - 1; i++) {
        tildes += textRows[i] + "\r\n";
    }

    if (n == 0) {
        // No Tildes in first row
        tildes = "\r\n";
    } else {
        tildes += textRows[n-1] + "\r\n";
    }

    // Draw Tildes from [n, rows)
    for (int i = n, m = editorConfig.getWindowRows() - 1; i < m; i++) {
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
        if (read(STDIN_FILENO, seq, 2) == 2 && seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return ARROW_UP;
                case 'B': return ARROW_DOWN;
                case 'C': return ARROW_RIGHT;
                case 'D': return ARROW_LEFT;
            }
        } 
    }

    return ch;
}