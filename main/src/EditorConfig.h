/*******************************************************
 * Editor's Configuration
 *
 * @author Vikas Choudhary
 * @date   06/09/2023 
 ******************************************************/
#ifndef EDITOR_CONFIG_H
#define EDITOR_CONFIG_H

#include <sys/ioctl.h>

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
public:
    EditorConfig();
    void enableRawMode(void);
    void disableRawMode(void);
};

#endif // EDITOR_CONFIG_H