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
    BACKSPACE = 8,
    HORIZONTAL_TAB = 9,
    NEWLINE = 13,
    ARROW_LEFT = 256,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    HOME_KEY,
    END_KEY,
    DELETE
};

class EditorConfig {
private:
    size_t currRow;
    size_t currCol;
    size_t tabLength;
    struct winsize ws;
    struct termios rawMode;
    struct termios canonicalMode;

    // Initilize Editor configuration
    void initEditorConfig(void);

    // Getters
    void getWindowsSize(void);
    void getCanonicalMode(void);
    void getRawMode(void);
    
public:
    // Constructor
    EditorConfig();

    // Getters
    size_t getWindowRows(void);
    size_t getWindowCols(void);
    size_t getCurrRow(void);
    size_t getCurrCol(void);
    size_t getTabLength(void);

    // Setters
    void setCursorToTopLeft(void);
    void setCursorToBottomLeft(void);
    
    // Update Editor mode
    void enableRawMode(void);
    void disableRawMode(void);
    
    // Update Cursor
    void updateCursor(void);
    void updateCurrRow(size_t newRow);
    void updateCurrCol(size_t newCol);
    void updateCursor(size_t newRow, size_t newCol);
    void updateCursor(int ch, const vector<string>& textRows);

    // Redraw line
    void redraw(const string& row);
};

#endif // EDITOR_CONFIG_H