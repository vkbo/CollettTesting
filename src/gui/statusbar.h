#ifndef GUIMAINSTATUS_H
#define GUIMAINSTATUS_H

#include <QStatusBar>

class GuiMainStatus : public QStatusBar
{
    Q_OBJECT

public:
    GuiMainStatus(QWidget *parent=nullptr);
    ~GuiMainStatus();

private:

};
#endif // GUIMAINSTATUS_H
