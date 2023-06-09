/*******************************************************
 * Editor's Configuration
 *
 * @author Vikas Choudhary
 * @date   06/09/2023 
 ******************************************************/
#include <stdlib.h>
#include <sys/ioctl.h>
#include "EditorConfig.h"

EditorConfig::EditorConfig() {
    initEditorConfig();
}

// Initialize editor configruation
void EditorConfig::initEditorConfig(void) {
    getWindowsSize();
    getCanonicalMode();
    getRawMode();
    currRow = dimension.getRows();
    currCol = 0;
}

// Get window size
void EditorConfig::getWindowsSize(void) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
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