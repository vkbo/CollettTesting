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

#ifndef COL_STORYTREE_H
#define COL_STORYTREE_H

#include "storyitem.h"

#include <QHash>
#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QUuid>
#include <QXmlStreamWriter>

namespace Collett {

class StoryTree : public QObject
{
    Q_OBJECT

public:
    StoryTree(QObject *parent=nullptr);
    ~StoryTree();

    StoryItem *itemWithHandle(const QString &handle);
    StoryItem *itemAt(int position);
    int count() const;

    void createItem(StoryItem::ItemType type, const QString &title, qsizetype position=-1);
    void toXML(const QString &nsCol, const QString &nsItm, QXmlStreamWriter &xmlWriter);

public slots:
    void updateItemCounts();

private:
    QHash<QString, StoryItem *> m_tree;
    QStringList m_order;

};
} // namespace Collett

#endif // COL_STORYTREE_H
