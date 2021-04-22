#include "mainmenu.h"

#include <QAction>
#include <QMenuBar>

GuiMainMenu::GuiMainMenu(QWidget *parent) : QMenuBar(parent)
{
    buildProjectMenu();
}

GuiMainMenu::~GuiMainMenu()
{
}

//
// Menu Builders
//

void GuiMainMenu::buildProjectMenu()
{

    // Project
    QMenu *projMenu = this->addMenu(tr("&Project"));

    // Project > New Project
    QAction *aNewProject = new QAction(tr("New Project"), this);
    aNewProject->setStatusTip(tr("Create new project"));
    projMenu->addAction(aNewProject);

    return;
}
