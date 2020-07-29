#include "collett.h"
#include "guimain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication cltApp(argc, argv);
    QCoreApplication::setOrganizationName("Collett");
    QCoreApplication::setOrganizationDomain("vkbo.net");
    QCoreApplication::setApplicationName("Collett");
    GuiMain cltGUI;
    cltGUI.show();
    return cltApp.exec();
}
