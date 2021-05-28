/*
Collett – Project Tree Class
============================

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

#include "projecttree.h"
#include "item.h"

#include <QObject>
#include <QUuid>
#include <QString>
#include <QStringList>

namespace Collett {

ColProjectTree::ColProjectTree(QObject *parent)
    : QObject(parent)
{
}

/*
    Access Methods
    ==============
*/

ColItem *ColProjectTree::itemWithHandle(const QString &handle) {
    return m_tree.value(handle, nullptr);
}

QStringList ColProjectTree::handles() const {
    return m_order;
}

/*
    Add Functions
    =============
*/

void ColProjectTree::addItem(const QString &title, const QString &parent, const ColItem::ItemType &type) {
    QString handle = QUuid::createUuid().toString(QUuid::WithoutBraces);
    addItem(title, handle, parent, type);
}

void ColProjectTree::addItem(const QString &title, const QString &handle, const QString &parent, const ColItem::ItemType &type) {
    ColItem *item = new ColItem(title, handle, parent, type);
    m_order.append(item->handle());
    m_tree.insert(item->handle(), item);
}

} // namespace Collett
