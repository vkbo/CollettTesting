/*
Collett – GUI Main Menu Class
=============================

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

#include "mainmenu.h"

#include <QKeySequence>

namespace Collett {

GuiMainMenu::GuiMainMenu(QWidget *parent) : QMenuBar(parent) {

    buildProjectMenu();
    buildContentMenu();
    buildFormatMenu();

}

GuiMainMenu::~GuiMainMenu() {
}

//
// Menu Builders
//

void GuiMainMenu::buildProjectMenu() {

    // Project
    m_menuProject = this->addMenu(tr("&Project"));

    // Project > New Project
    a_projNew = m_menuProject->addAction(tr("&New Project"));
    a_projNew->setStatusTip(tr("Create new project"));

    // Project > Open Project
    a_projOpen = m_menuProject->addAction(tr("&Open Project"));
    a_projOpen->setStatusTip(tr("Open project"));
    a_projOpen->setShortcut(QKeySequence("Ctrl+O"));

    // Project > Save Project
    a_projSave = m_menuProject->addAction(tr("&Save Project"));
    a_projSave->setStatusTip(tr("Save project"));
    a_projSave->setShortcut(QKeySequence("Ctrl+S"));

    return;
}

void GuiMainMenu::buildContentMenu() {

    // Content
    m_menuContent = this->addMenu(tr("&Content"));

    // Content > New Page
    a_contNewPage = m_menuContent->addAction(tr("New &Page"));
    a_contNewPage->setStatusTip(tr("Create a new page in the project"));
    a_contNewPage->setShortcut(QKeySequence("Ctrl+N, P"));

    // Content > New Chapter
    a_contNewChapter = m_menuContent->addAction(tr("New &Chapter"));
    a_contNewChapter->setStatusTip(tr("Create a new chapter in the project"));
    a_contNewChapter->setShortcut(QKeySequence("Ctrl+N, C"));

    // Content > New Scene
    a_contNewScene = m_menuContent->addAction(tr("New &Scene"));
    a_contNewScene->setStatusTip(tr("Create a new scene in the project"));
    a_contNewScene->setShortcut(QKeySequence("Ctrl+N, S"));

    // Content > New Note
    a_contNewNote = m_menuContent->addAction(tr("New &Note"));
    a_contNewNote->setStatusTip(tr("Create a new note in the project"));
    a_contNewNote->setShortcut(QKeySequence("Ctrl+N, N"));

    return;
}

void GuiMainMenu::buildFormatMenu() {

    // Format Menu
    m_menuFormat = this->addMenu(tr("&Format"));

    // Format > Emphasis
    a_fmtEmphasis = m_menuFormat->addAction(tr("Emphasis"));
    a_fmtEmphasis->setShortcut(QKeySequence("Ctrl+I"));

    return;
}

} // namespace Collett
