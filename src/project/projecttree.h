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

#ifndef COLPROJECTTREE_H
#define COLPROJECTTREE_H

#include "item.h"

#include <QHash>
#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QUuid>
#include <QXmlStreamWriter>

namespace Collett {

class ColProjectTree : public QObject
{
    Q_OBJECT

public:
    ColProjectTree(QObject *parent=nullptr);
    ~ColProjectTree();

    ColItem *itemWithHandle(const QString &handle);
    int count() const;

    ColItem *createItem(ColItem::ItemType type, const QString &title, ColItem *parent, int position=-1);
    void toXML(const QString &ns, QXmlStreamWriter &xmlWriter);

    ColItem *storyRootItem();
    ColItem *notesRootItem();

private:
    QHash<QString, ColItem *> m_tree;

    ColItem *m_storyRoot;
    ColItem *m_notesRoot;

};
} // namespace Collett

#endif // COLPROJECTTREE_H
