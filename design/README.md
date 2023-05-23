# Design 
## Editor[In progress]
Text editor is a CLI or GUI based application that allows user to create,
update and delete text file. We will design first CLI based editor in which
we can edit one file at a time.

The CLI editor has two supported modes:
 1. EDIT - In this mode, user can enter text information using keyboard. 
    He can edit new text, remove existing text or update text. 
 2. COMMAND - In this mode, user can perform file operation like save, 
    search, find and replace, find and replace all and exit from editor etc.

User can start text application from terminal using one of the following commands
- ```$ panda```
- ```$ panda <file_name>```

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
    editText();
    saveFile();
    saveAsFile(const string& newFileName);
    deleteFile();
    exitFromEditor();
public:
    Editor();
    Editor(const string& fileName);
    handleFileOperator(const string& command);
    updateMode(const EditorMode& newMode);
}
```
