/*
Collett – Main GUI Class
========================

This file is a part of Collett
Copyright 2020–2021, Veronica Berglyd Olsen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "guimain.h"
#include "data.h"
#include "settings.h"
#include "document.h"
#include "doceditor.h"
#include "mainmenu.h"
#include "noveltree.h"
#include "statusbar.h"

#include <QCloseEvent>
#include <QList>
#include <QMainWindow>
#include <QSplitter>
#include <QDir>

namespace Collett {

GuiMain::GuiMain(QWidget *parent) : QMainWindow(parent) {

    // Create Main Data Object
    mainData = new ColData(this);

    // Main GUI Elements
    guiMainStatus = new GuiMainStatus(this);
    guiDocEditor  = new GuiDocEditor(this, mainData);
    guiNovelTree  = new GuiNovelTree(this);
    guiMainMenu   = new GuiMainMenu(this);

    // Assemble Main Window
    qtwSplitMain = new QSplitter(Qt::Horizontal, this);
    qtwSplitMain->setContentsMargins(4, 4, 4, 4);
    qtwSplitMain->setOpaqueResize(false);
    qtwSplitMain->addWidget(guiNovelTree);
    qtwSplitMain->addWidget(guiDocEditor);

    // Set Main Window Elements
    this->setMenuBar(guiMainMenu);
    this->setCentralWidget(qtwSplitMain);
    this->setStatusBar(guiMainStatus);

    // Apply Settings
    ColSettings *mainConf = ColSettings::instance();
    this->resize(mainConf->mainWindowSize());
    qtwSplitMain->setSizes(mainConf->mainSplitSizes());

    // Load Something
    openProject(QDir("../Sample"));

    guiDocEditor->openDocument("test");
    guiDocEditor->saveDocument();

    return;
}

/*
    Project Functions
    =================
*/

bool GuiMain::openProject(const QDir projPath) {
    return mainData->openProject(projPath);
}

/*
    Document Functions
    ==================
*/

bool GuiMain::openDocument(const QString handle) {
    return guiDocEditor->openDocument(handle);
}

/*
    GUI Functions
    =============
*/

bool GuiMain::closeMain() {

    // Save Settings
    ColSettings *mainConf = ColSettings::instance();
    if (!this->isFullScreen()) {
        mainConf->setMainWindowSize(this->size());
        mainConf->setMainSplitSizes(qtwSplitMain->sizes());
    }
    mainConf->flushSettings();

    return true;
}

/*
    Events
    ======
*/

void GuiMain::closeEvent(QCloseEvent *theEvent) {
    if (closeMain()) {
        theEvent->accept();
    } else {
        theEvent->ignore();
    }
}

} // namespace Collett
