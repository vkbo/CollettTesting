#include "guimain.h"
#include "mainmenu.h"
#include "statusbar.h"
#include "docdetails.h"
#include "doceditor.h"
#include "docviewer.h"
#include "doctree.h"
#include "noticebar.h"
#include "searchbar.h"
#include "viewdetails.h"

#include <QCloseEvent>
#include <QFrame>
#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPointer>

GuiMain::GuiMain(QWidget *parent) : QMainWindow(parent)
{
    Project *theProject = new Project();

    // Main GUI Elements
    QPointer<GuiMainStatus>     statusBar = new GuiMainStatus(this);
    QPointer<GuiNoticeBar>      noticeBar = new GuiNoticeBar(this);
    QPointer<GuiDocEditor>      docEditor = new GuiDocEditor(this);
    QPointer<GuiDocViewer>      docViewer = new GuiDocViewer(this);
    QPointer<GuiDocViewDetails> viewMeta  = new GuiDocViewDetails(this);
    QPointer<GuiSearchBar>      searchBar = new GuiSearchBar(this);
    QPointer<GuiDocTree>        treeView  = new GuiDocTree(this);
    QPointer<GuiDocDetails>     treeMeta  = new GuiDocDetails(this);
    QPointer<GuiMainMenu>       mainMenu  = new GuiMainMenu(this);

    // Assemble Main Window
    QFrame      *treePane = new QFrame(this);
    QVBoxLayout *treeBox  = new QVBoxLayout();
    treeBox->setContentsMargins(0, 0, 0, 0);
    treeBox->addWidget(treeView);
    treeBox->addWidget(treeMeta);
    treePane->setLayout(treeBox);

    QFrame      *editPane = new QFrame(this);
    QVBoxLayout *docEdit  = new QVBoxLayout();
    docEdit->setContentsMargins(0, 0, 0, 0);
    docEdit->addWidget(searchBar);
    docEdit->addWidget(noticeBar);
    docEdit->addWidget(docEditor);
    editPane->setLayout(docEdit);

    QFrame      *viewPane = new QFrame(this);
    QVBoxLayout *docView  = new QVBoxLayout();
    docView->setContentsMargins(0, 0, 0, 0);
    docView->addWidget(docViewer);
    docView->addWidget(viewMeta);
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

    theProject->openProject("../Source/sample/");

    return;
}

GuiMain::~GuiMain()
{
}

/*
 * Internal Functions
 */

bool GuiMain::closeMain()
{
    if (!this->isFullScreen()) {
        mainConf.setValue("GuiMain/winSize", this->size());
    }
    return true;
}

/*
 * Events
 */

void GuiMain::closeEvent(QCloseEvent *theEvent)
{
    if (closeMain()) {
        theEvent->accept();
    } else {
        theEvent->ignore();
    }
}