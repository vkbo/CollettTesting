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
#include "data.h"

#include <QListView>

namespace Collett {

GuiNovelTree::GuiNovelTree(QWidget *parent)
    : QListView(parent)
{

    m_data = CollettData::instance();

    // Build GUI
    // this->setIconSize(QSize(13,13));
    // this->setExpandsOnDoubleClick(true);
    // this->setIndentation(13);
    // this->setColumnCount(2);
    // this->setHeaderLabels(QStringList() << "Title" << "Words");
    // this->hideColumn(3);

    // QTreeWidgetItem *treeHead = this->headerItem();
    // treeHead->setTextAlignment(1, Qt::AlignRight);

    // // Allow move by drag'n'drop
    // this->setDragEnabled(true);
    // this->setDragDropMode(QAbstractItemView::InternalMove);

    // // But don't allow drop on root level
    // QTreeWidgetItem *trRoot = this->invisibleRootItem();
    // trRoot->setFlags(trRoot->flags() ^ Qt::ItemIsDropEnabled);

    return;
}

} // namespace Collett
