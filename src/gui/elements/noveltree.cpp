/*
Collett – GUI Novel Tree Class
==============================

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

#include "noveltree.h"

#include <QTreeWidget>

#define C_NAME   0
#define C_COUNT  1
#define C_FLAGS  2
#define C_HANDLE 3

GuiNovelTree::GuiNovelTree(QWidget *parent) : QTreeWidget(parent) {

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

GuiNovelTree::~GuiNovelTree() {
}
