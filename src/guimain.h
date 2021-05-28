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

#ifndef GUIMAIN_H
#define GUIMAIN_H

#include "data.h"
#include "doceditor.h"
#include "mainmenu.h"
#include "noveltree.h"
#include "statusbar.h"
#include "editarea.h"

#include <QObject>
#include <QMainWindow>
#include <QSplitter>
#include <QDir>

namespace Collett {

class GuiMain : public QMainWindow
{
    Q_OBJECT

public:
    GuiMain(QWidget *parent=nullptr);
    ~GuiMain() {};

    void openProject(const QString &path);
    bool saveProject();
    bool closeProject();

    bool openDocument(const QString &handle);
    bool saveDocument();
    bool closeDocument();

    bool closeMain();

private:
    CollettData *m_data;

    // Main GUI Elements
    GuiEditArea   *m_editArea;
    GuiMainStatus *m_statusBar;
    GuiNovelTree  *m_novelTree;
    GuiMainMenu   *m_mainMenu;

    // GUI Widgets
    QSplitter *m_splitMain;

    // Events
    virtual void closeEvent(QCloseEvent*);

};
} // namespace Collett

#endif // GUIMAIN_H
