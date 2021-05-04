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
#include "mainmenu.h"
#include "statusbar.h"
#include "doceditor.h"
#include "noveltree.h"

#include <QCloseEvent>
#include <QFrame>
#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPointer>

GuiMain::GuiMain(QWidget *parent) : QMainWindow(parent) {

    Project *theProject = new Project();

    // Main GUI Elements
    QPointer<GuiMainStatus> statusBar = new GuiMainStatus(this);
    QPointer<GuiDocEditor>  docEditor = new GuiDocEditor(this);
    QPointer<GuiNovelTree>  novelTree = new GuiNovelTree(this);
    QPointer<GuiMainMenu>   mainMenu  = new GuiMainMenu(this);

    // Assemble Main Window
    QFrame      *treePane = new QFrame(this);
    QVBoxLayout *treeBox  = new QVBoxLayout();
    treeBox->setContentsMargins(0, 0, 0, 0);
    treeBox->addWidget(novelTree);
    treePane->setLayout(treeBox);

    QFrame      *editPane = new QFrame(this);
    QVBoxLayout *docEdit  = new QVBoxLayout();
    docEdit->setContentsMargins(0, 0, 0, 0);
    docEdit->addWidget(docEditor);
    editPane->setLayout(docEdit);

    QFrame      *viewPane = new QFrame(this);
    QVBoxLayout *docView  = new QVBoxLayout();
    docView->setContentsMargins(0, 0, 0, 0);
    viewPane->setLayout(docView);

    QSplitter *splitView = new QSplitter(Qt::Horizontal, this);
    splitView->setOpaqueResize(false);
    splitView->addWidget(editPane);
    splitView->addWidget(viewPane);

    QSplitter *splitMain = new QSplitter(Qt::Horizontal, this);
    splitMain->setContentsMargins(4, 4, 4, 4);
    splitMain->setOpaqueResize(false);
    splitMain->addWidget(treePane);
    splitMain->addWidget(splitView);

    this->setCentralWidget(splitMain);

    // Set Main Window Elements
    this->setMenuBar(mainMenu);
    this->setStatusBar(statusBar);

    this->resize(QSize(1400, 800));

    theProject->openProject("../Source/sample/");

    return;
}

GuiMain::~GuiMain() {
}

/*
 * Internal Functions
 */

bool GuiMain::closeMain() {
    if (!this->isFullScreen()) {
        mainConf.setValue("GuiMain/winSize", this->size());
    }
    return true;
}

/*
 * Events
 */

void GuiMain::closeEvent(QCloseEvent *theEvent) {
    if (closeMain()) {
        theEvent->accept();
    } else {
        theEvent->ignore();
    }
}