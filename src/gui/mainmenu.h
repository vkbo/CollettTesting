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

#ifndef GUIMAINMENU_H
#define GUIMAINMENU_H

#include <QObject>
#include <QAction>
#include <QMenuBar>

namespace Collett {

class GuiMainMenu : public QMenuBar
{
    Q_OBJECT

public:
    GuiMainMenu(QWidget *parent=nullptr);
    ~GuiMainMenu();

private:
    void buildProjectMenu();
    void buildContentMenu();
    void buildEditMenu();
    void buildViewMenu();
    void buildFormatMenu();
    void buildToolsMenu();
    void buildHelpMenu();

    // Menus
    QMenu *m_menuProject;
    QMenu *m_menuContent;
    QMenu *m_menuFormat;

    // Project Menu
    QAction *a_projNew;
    QAction *a_projOpen;
    QAction *a_projSave;

    // Content Menu
    QAction *a_contNewPage;
    QAction *a_contNewChapter;
    QAction *a_contNewScene;
    QAction *a_contNewNote;

    // Format Menu
    QAction *a_fmtEmphasis;
    QAction *a_fmtStrong;
    QAction *a_fmtStike;

};
} // namespace Collett

#endif // GUIMAINMENU_H
