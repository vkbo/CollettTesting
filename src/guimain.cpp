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
#include "textutils.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDir>
#include <QList>
#include <QMainWindow>
#include <QSplitter>
#include <QString>

namespace Collett {

GuiMain::GuiMain(QWidget *parent) : QMainWindow(parent) {

    // Create Main Data Object
    m_data = CollettData::instance();

    // Main GUI Elements
    m_mainMenu  = new GuiMainMenu(this);
    m_novelTree = new GuiNovelTree(this);
    m_docEditor = new GuiDocEditor(this);
    m_statusBar = new GuiMainStatus(this);

    // Assemble Main Window
    m_splitMain = new QSplitter(Qt::Horizontal, this);
    m_splitMain->setContentsMargins(4, 4, 4, 4);
    m_splitMain->setOpaqueResize(false);
    m_splitMain->addWidget(m_novelTree);
    m_splitMain->addWidget(m_docEditor);

    // Set Main Window Elements
    this->setMenuBar(m_mainMenu);
    this->setCentralWidget(m_splitMain);
    this->setStatusBar(m_statusBar);

    // Apply Settings
    CollettSettings *mainConf = CollettSettings::instance();
    this->resize(mainConf->mainWindowSize());
    m_splitMain->setSizes(mainConf->mainSplitSizes());

    // Connect Signals
    connect(
        m_novelTree, SIGNAL(doubleClicked(const QModelIndex &)),
        this, SLOT(doStoryTreeDoubleClick(const QModelIndex &))
    );

    // Finalise
    this->setWindowTitle(
        tr("%1 %2 Version %3").arg(qApp->applicationName(), "–", qApp->applicationVersion())
    );

    return;
}

/*
    Project Functions
    =================
*/

void GuiMain::openProject(const QString &path) {
    m_data->openProject(path);
    QItemSelectionModel *m = m_novelTree->selectionModel();
    m_novelTree->setModel(m_data->storyModel());
    delete m;

    QString lastHandle = m_data->project()->lastOpenDocument();
    if (TextUtils::isHandle(lastHandle)) {
        openDocument(lastHandle);
    }
}

bool GuiMain::saveProject() {
    return m_data->saveProject();
}

/*
    Document Functions
    ==================
*/

void GuiMain::openDocument(const QString &handle) {
    if (m_docEditor->hasBeenModified()) {
        m_docEditor->saveDocument();
    }
    if (m_docEditor->openDocument(handle)) {
        m_data->project()->setLastOpenDocument(handle);
    };
}

/*
    GUI Functions
    =============
*/

bool GuiMain::closeMain() {

    m_docEditor->saveDocument();
    saveProject();

    // Save Settings
    CollettSettings *mainConf = CollettSettings::instance();
    if (!this->isFullScreen()) {
        mainConf->setMainWindowSize(this->size());
        mainConf->setMainSplitSizes(m_splitMain->sizes());
    }
    mainConf->flushSettings();

    return true;
}

/*
    Slots
    =====
*/

void GuiMain::doStoryTreeDoubleClick(const QModelIndex &index) {
    if (!index.isValid()) {
        return;
    }

    QString handle = m_novelTree->model()->data(index, Qt::UserRole).toString();
    if (TextUtils::isHandle(handle)) {
        openDocument(handle);
        qDebug() << "Opening document:" << handle;
    }
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
