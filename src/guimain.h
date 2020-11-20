#ifndef GUIMAIN_H
#define GUIMAIN_H

#include "core.h"

#include <QMainWindow>
#include <QSettings>

class GuiMain : public QMainWindow
{
    Q_OBJECT

public:
    GuiMain(QWidget *parent=nullptr);
    ~GuiMain();

    Project *theProject;

private:
    QSettings mainConf;

    bool closeMain();

    // Events
    virtual void closeEvent(QCloseEvent*);

};

#endif // GUIMAIN_H
