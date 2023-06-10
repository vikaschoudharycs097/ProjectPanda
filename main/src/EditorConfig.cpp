/*******************************************************
 * Editor's Configuration
 *
 * @author Vikas Choudhary
 * @date   06/09/2023 
 ******************************************************/
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "EditorConfig.h"
using std::string;
using std::to_string;

EditorConfig::EditorConfig() {
    initEditorConfig();
}

// Initialize editor configruation
void EditorConfig::initEditorConfig(void) {
    getWindowsSize();
    getCanonicalMode();
    getRawMode();
    currRow = ws.ws_row - 1;
    currCol = 0;
    updateCursor();
}

// Get window size
void EditorConfig::getWindowsSize(void) {
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != 0) {
        exit(-1);
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
}

// Enable Raw mode
void EditorConfig::enableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawMode);
}

// Disable Raw mode
void EditorConfig::disableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &canonicalMode);
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

void EditorConfig::updateCursor() {
    // Move the cursor to current position specified by (currRow, currCol)
    const string currRowStr = to_string(currRow + 1);
    const string currColStr = to_string(currCol + 1);
    const string escapeSeq = "\x1b[" + currRowStr + ";" + currColStr + "H";
    write(STDOUT_FILENO, escapeSeq.c_str(), 4 + currRowStr.length() + currColStr.length());
}

// Return the number of rows in window
int EditorConfig::getWindowRows() {
    return ws.ws_row;
}

// Return the number of columns in window
int EditorConfig::getWindowColumns() {
    return ws.ws_col;
}