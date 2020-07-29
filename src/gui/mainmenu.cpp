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
    QMenu *projMenu = this->addMenu("&Project");

    // Project > New Project
    QAction *aNewProject = new QAction("New Project", this);
    aNewProject->setStatusTip("Create new project");
    // self.aNewProject.triggered.connect(lambda : self.theParent.newProject(None))
    projMenu->addAction(aNewProject);

    return;
}
