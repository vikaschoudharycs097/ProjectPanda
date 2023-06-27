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
    if (fileName != "") {
        string line;
        fstream file(fileName, fstream::in | fstream::app);
        while (!file.eof()) {
            getline(file, line);
            textRows.push_back(line);
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
            case HOME_KEY:
            case END_KEY:
                editorConfig.moveCursor(ch, textRows);
                break;
            case '\0':
                break;
            default:
                insertChar(ch, editorConfig.getCurrRow(), editorConfig.getCurrCol());
                write(STDOUT_FILENO, &ch, 1);
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
    char ch = '\0';
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
                case '1': 
                case '7':
                case 'H':
                    return HOME_KEY;
                case '4':
                case '8':
                case 'F':
                    return END_KEY;
            }
        } 
    }

    return ch;
}

// Insert a character at given position
void Editor::insertChar(int ch, size_t row, size_t col) {
    switch (ch) {
        case NEWLINE:
            if (row + 1 == textRows.size()) {
                write(STDOUT_FILENO, "\x1b[2K", 4);
                textRows.push_back("");
            } else {
                textRows.push_back("");
                for (size_t i = textRows.size() - 1; i > row + 1; i--) {
                    textRows[i] = textRows[i-1];
                }
                textRows[row + 1] = "";
            }
            editorConfig.updateCurrentPositionAndCursor(row + 1, 0);
            break;
        case HORIZONTAL_TAB:
            break;
        default:
            if (col == textRows[row].size()) {
                textRows[row].push_back(ch);
            } else {
                textRows[row].push_back(ch);
                for (size_t i = textRows[row].size() - 2; i > col; i--) {
                    textRows[row][i] = textRows[row][i-1];
                }
                textRows[row][col] = ch;
            }
            editorConfig.updateCurrCol(col + 1);
            break;
    }
}