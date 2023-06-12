/*******************************************************
 * Editor's Configuration
 *
 * @author Vikas Choudhary
 * @date   06/09/2023 
 ******************************************************/
#ifndef EDITOR_CONFIG_H
#define EDITOR_CONFIG_H

#include <sys/ioctl.h>

enum EditorKey {
    ARROW_LEFT = 256,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN
};

class EditorConfig {
private:
    int currRow;
    int currCol;
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
    int getWindowRows(void);
    int getWindowColumns(void);
    void updateCurrentPosition(int ch);
};

#endif // EDITOR_CONFIG_H