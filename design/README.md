# Design 
## Editor[In progress]
The CLI editor has two supported modes:
 1. EDIT - In this mode, user can enter text information using keyboard. 
    He can edit new text, remove existing text or update text. 
 2. COMMAND - In this mode, user can perform file operation like save, 
    search, find and replace, find and replace all and exit from editor etc.

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