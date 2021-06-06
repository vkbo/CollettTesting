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

#include "collett.h"
#include "data.h"
#include "noveltree.h"
#include "statusbar.h"
#include "doceditor.h"
#include "maintoolbar.h"

#include <QDir>
#include <QMainWindow>
#include <QModelIndex>
#include <QObject>
#include <QSplitter>

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

    void openDocument(const QString &handle);
    bool saveDocument();
    bool closeDocument();

    bool closeMain();

public slots:

    void doStoryTreeDoubleClick(const QModelIndex &index);
    void forwardDocAction(Collett::DocAction action);

private:
    CollettData *m_data;

    // Main GUI Elements
    GuiMainToolBar *m_mainToolBar;
    GuiNovelTree   *m_novelTree;
    GuiDocEditor   *m_docEditor;
    GuiMainStatus  *m_statusBar;

    // GUI Widgets
    QSplitter *m_splitMain;

    // Events
    virtual void closeEvent(QCloseEvent*);

};
} // namespace Collett

#endif // GUIMAIN_H
