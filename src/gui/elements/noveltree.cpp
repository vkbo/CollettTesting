#include "noveltree.h"

#include <QTreeWidget>

#define C_NAME   0
#define C_COUNT  1
#define C_FLAGS  2
#define C_HANDLE 3

GuiNovelTree::GuiNovelTree(QWidget *parent) : QTreeWidget(parent)
{
    // Build GUI
    this->setIconSize(QSize(13,13));
    this->setExpandsOnDoubleClick(true);
    this->setIndentation(13);
    this->setColumnCount(4);
    this->setHeaderLabels(QStringList() << "Label" << "Words" << "Flags" << "Handle");
    this->hideColumn(C_HANDLE);

    QTreeWidgetItem *treeHead = this->headerItem();
    treeHead->setTextAlignment(C_COUNT, Qt::AlignRight);

    // Allow move by drag'n'drop
    this->setDragEnabled(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);

    // But don't allow drop on root level
    QTreeWidgetItem *trRoot = this->invisibleRootItem();
    trRoot->setFlags(trRoot->flags() ^ Qt::ItemIsDropEnabled);

    return;
}

GuiNovelTree::~GuiNovelTree()
{
}
