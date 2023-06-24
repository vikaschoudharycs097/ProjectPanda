/*******************************************************
 * Editor's Configuration
 *
 * @author Vikas Choudhary
 * @date   06/09/2023 
 ******************************************************/
#ifndef EDITOR_CONFIG_H
#define EDITOR_CONFIG_H

#include <string>
#include <vector>
#include <sys/ioctl.h>
using std::string;
using std::vector;

enum EditorKey {
    HORIZONTAL_TAB = 9,
    NEWLINE = 13,
    ARROW_LEFT = 256,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    HOME_KEY,
    END_KEY
};

class EditorConfig {
private:
    size_t currRow;
    size_t currCol;
    size_t tabLength;
    struct winsize ws;
    struct termios canonicalMode;
    struct termios rawMode;

    // Private member functions
    void initEditorConfig(void);
    void getWindowsSize(void);
    void getCanonicalMode(void);
    void getRawMode(void);
    void updateCursor(void);
    
public:
    EditorConfig();
    void enableRawMode(void);
    void disableRawMode(void);
    void setCursorToTopLeft(void);
    void setCursorToBottomLeft(void);
    size_t getWindowRows(void);
    size_t getWindowCols(void);
    size_t getCurrRow(void);
    size_t getCurrCol(void);
    void updateCurrRow(size_t newRow);
    void updateCurrCol(size_t newCol);
    void updateCurrentPosition(int ch, const vector<string>& textRows);
};

#endif // EDITOR_CONFIG_H