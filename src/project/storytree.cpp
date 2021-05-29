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

#include "storytree.h"
#include "storyitem.h"

#include <QObject>
#include <QString>
#include <QXmlStreamWriter>
#include <QDebug>

namespace Collett {

StoryTree::StoryTree(QObject *parent)
    : QObject(parent)
{
}

StoryTree::~StoryTree() {
    qDeleteAll(m_tree);
}

/*
    Access Methods
    ==============
*/

StoryItem *StoryTree::itemWithHandle(const QString &handle) {
    return m_tree.value(handle, nullptr);
}

int StoryTree::count() const {
    return m_tree.count();
}

/*
    Add Functions
    =============
*/

void StoryTree::createItem(StoryItem::ItemType type, const QString &title, qsizetype position) {
    StoryItem *item = new StoryItem();
    item->initItem(type, title);
    m_tree.insert(item->handle(), item);
    if (position < 0 || position >= m_order.size()) {
        m_order.append(item->handle());
    } else {
        m_order.insert(position, item->handle());
    }
}

/*
    XML Functions
    =============
*/

void StoryTree::toXML(const QString &nsCol, const QString &nsItm, QXmlStreamWriter &xmlWriter) {

    xmlWriter.writeStartElement(nsCol, "story");
    xmlWriter.writeAttribute(nsItm, "count", QString::number(m_tree.size()));
    for (QString handle : m_order) {
        StoryItem *item = itemWithHandle(handle);
        if (item) {
            item->toXml(nsCol, nsItm, xmlWriter);
        }
    }
    xmlWriter.writeEndElement();

    return;
}

} // namespace Collett
