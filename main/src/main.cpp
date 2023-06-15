/***************************************
 * main function
 * 
 * @author Vikas Choudhary
 * @date 05/30/2023
 **************************************/
#include "Editor.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        Editor editor(argv[1]);
        editor.start();
    } else {
        Editor editor;
        editor.start();
    }
    return 0;
}