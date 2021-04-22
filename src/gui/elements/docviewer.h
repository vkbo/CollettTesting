#ifndef GUIDOCVIEWER_H
#define GUIDOCVIEWER_H

#include <QTextBrowser>

class GuiDocViewer : public QTextBrowser
{
    Q_OBJECT

public:
    GuiDocViewer(QWidget *parent=nullptr);
    ~GuiDocViewer();

private:

};
#endif // GUIDOCVIEWER_H
