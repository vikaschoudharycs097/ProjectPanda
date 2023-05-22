# Project Panda: An Advanced C++ IDE
A C++ IDE with both CLI and GUI experiences. The initial design is for Linux 
Based Operating Systems(OS). This project will be developed in incremental 
way, initially with minimal functional support.

## Components of Project Panda IDE
- A CLI and GUI based editor
- g++ and clang++ compiler supports
- An auto generated makefile with the support of manual update
- GDB debugger integration

## Functional Requirements
### Editor Requirements
1. User can create a file.
2. User can open an existing file.
3. User can delete a file.
4. User can modify file content.

## LLD Design 
### Editor[In progress]
The CLI editor has two supported modes 1) EDIT - In this mode, user can enter 
text information using keyboard. He can edit new text, remove existing text 
or update text. 2) COMMAND - In this mode, user can perform file operation like 
save, search, find and replace, find and replace all and exit from editor etc.

```
enum class EditorMode {
    EDIT,
    COMMAND
};

class Editor {
private:
    string fileName;
    string content;
    EditorMode currMode;
public:
    Editor();
    Editor(const string& fileName);
    handleFileOperator(const string& command);
    manageMode();
}
```