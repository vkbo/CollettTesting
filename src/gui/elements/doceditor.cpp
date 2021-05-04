#include "doceditor.h"

GuiDocEditor::GuiDocEditor(QWidget *parent) : QTextEdit(parent) {

    // Settings
    this->setAcceptRichText(true);

    this->setHtml("<h1>Hello World</h1><p>This is some text ...</p>");

    return;
}

GuiDocEditor::~GuiDocEditor()
{
}
