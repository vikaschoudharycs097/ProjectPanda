/*******************************************************
 * Editor's Configuration
 *
 * @author Vikas Choudhary
 * @date   06/09/2023 
 ******************************************************/
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "Error.h"
#include "EditorConfig.h"
using std::min;
using std::max;
using std::string;
using std::vector;
using std::to_string;

EditorConfig::EditorConfig() {
    initEditorConfig();
}

// Initialize editor configruation
void EditorConfig::initEditorConfig(void) {
    getWindowsSize();
    getCanonicalMode();
    getRawMode();
    currCol = 0;
    tabLength = 4;
    currRow = ws.ws_row - 1;
    updateCursor();
}

// Get window size
void EditorConfig::getWindowsSize(void) {
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != 0) {
        exit(Error::WINSIZE_EXTRACTION_FAILED);
    }
}

// Get Canonical mode
void EditorConfig::getCanonicalMode(void) {
    tcgetattr(STDIN_FILENO, &canonicalMode);
}

// Get Raw mode
void EditorConfig::getRawMode(void) {
    tcgetattr(STDIN_FILENO, &rawMode);

    // Disable ctrl-s, ctrl-q, ctrl-m and other miscellaneous flags
    rawMode.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);

    // Disable Output post processing
    rawMode.c_oflag &= ~(OPOST);

    // Set character size to 8 bits
    rawMode.c_cflag |= (CS8);

    // Disable echo, canonical mode, ctrl-z(or ctrl-y in mac), ctrl-c, ctrl-v
    rawMode.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

    // Set read time to 0.1 s
    rawMode.c_cc[VMIN] = 0;
    rawMode.c_cc[VTIME] = 1;
}

// Get the number of rows in window
size_t EditorConfig::getWindowRows() {
    return ws.ws_row;
}

// Get the number of columns in window
size_t EditorConfig::getWindowCols() {
    return ws.ws_col;
}

// Get row of cursor
size_t EditorConfig::getCurrRow(void) {
    return currRow;
}

// Get column of cursor
size_t EditorConfig::getCurrCol(void) {
    return currCol;
}

// Get Tab length
size_t EditorConfig::getTabLength(void) {
    return tabLength;
}

// Set cursor to (0, 0) - Top left
void EditorConfig::setCursorToTopLeft(void) {
    currRow = currCol = 0;
    updateCursor();
}

// Set cursor to (maxRows-1, 0) - Bottom left
void EditorConfig::setCursorToBottomLeft(void) {
    currRow = ws.ws_row - 1;
    currCol = 0;
    updateCursor();
}

// Enable Raw mode
void EditorConfig::enableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawMode);
}

// Disable Raw mode
void EditorConfig::disableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &canonicalMode);
}

// Update row of cursor
void EditorConfig::updateCurrRow(size_t newRow) {
    currRow = newRow;
}

// Update column of cursor
void EditorConfig::updateCurrCol(size_t newCol) {
    currCol = newCol;
}

// Update cursor to (currRow, currCol)
void EditorConfig::updateCursor() {
    char escapeSeq[20];
    sprintf(escapeSeq, "\x1b[%ld;%ldH", currRow + 1, currCol + 1);
    write(STDOUT_FILENO, escapeSeq, strlen(escapeSeq));
}

// Update current position based on input
void EditorConfig::updateCursor(int ch, const vector<string>& textRows) {
    switch (ch) {
        case ARROW_UP:
            if (currRow > 0) {
                currRow--;
                currCol = min(currCol, max(0ul, textRows[currRow].size() - 1));
            }
            break;
        case ARROW_LEFT:
            if (currCol > 0) {
                currCol--;
            }
            break;
        case ARROW_DOWN:
            if (currRow < textRows.size() - 1) {
                currRow++;
                currCol = min(currCol, max(0ul, textRows[currRow].size() - 1));
            }
            break;
        case ARROW_RIGHT:
            if (currCol < textRows[currRow].size() - 1) {
                currCol++;
            }
            break;
        case HOME_KEY:
            currCol = 0;
            break;
        case END_KEY:
            currCol = max(0ul, textRows[currRow].size() - 1);
            break;
    }
    
    // Update cursor to new position
    updateCursor();
}

void EditorConfig::updateCursor(size_t newRow, size_t newCol) {
    currRow = newRow;
    currCol = newCol;
    updateCursor();
}

// Redraw line
void EditorConfig::redraw(const string& row) {
    write(STDOUT_FILENO, "\x1b[2K", 4);
    
    // Store existing cursor position
    size_t rowPos = currRow;
    size_t colPos = currCol;
    updateCursor(rowPos, 0);
    write(STDOUT_FILENO, row.c_str(), row.size());
    updateCursor(rowPos, colPos);
}