#include "mainmenu.h"

#include <QKeySequence>

GuiMainMenu::GuiMainMenu(QWidget *parent) : QMenuBar(parent)
{
    buildProjectMenu();
    buildFormatMenu();
}

GuiMainMenu::~GuiMainMenu()
{
}

//
// Menu Builders
//

void GuiMainMenu::buildProjectMenu() {

    // Project
    projMenu = this->addMenu(tr("&Project"));

    // Project > New Project
    QAction *aNewProject = new QAction(tr("New Project"), this);
    aNewProject->setStatusTip(tr("Create new project"));
    projMenu->addAction(aNewProject);

    return;
}

void GuiMainMenu::buildFormatMenu() {

    // Format Menu
    fmtMenu = this->addMenu(tr("&Format"));

    // Format > Emphasis
    aFmtEmph = fmtMenu->addAction(tr("Emphasis"));
    aFmtEmph->setShortcut(QKeySequence("Ctrl+I"));

    return;
}
