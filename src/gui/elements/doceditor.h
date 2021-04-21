#ifndef GUIDOCEDITOR_H
#define GUIDOCEDITOR_H

#include <QTextEdit>

class GuiDocEditor : public QTextEdit
{
    Q_OBJECT

public:
    GuiDocEditor(QWidget *parent=nullptr);
    ~GuiDocEditor();

private:

};
#endif // GUIDOCEDITOR_H
