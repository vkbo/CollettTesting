#ifndef GUIDOCVIEWER_H
#define GUIDOCVIEWER_H

#include <QTextBrowser>

class GuiDocViewer : public QTextBrowser
{
public:
    GuiDocViewer(QWidget *parent=nullptr);
    ~GuiDocViewer();

private:

};
#endif // GUIDOCVIEWER_H
