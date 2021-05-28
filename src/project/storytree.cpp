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
#include <QUuid>
#include <QXmlStreamWriter>

namespace Collett {

StoryTree::StoryTree(QObject *parent)
    : QObject(parent)
{
    m_rootItem = new StoryItem();
}

StoryTree::~StoryTree() {
    delete m_rootItem;
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
    Root Items
    ==========
*/

StoryItem *StoryTree::storyRootItem() {
    if (m_rootItem->isEmpty()) {
        m_rootItem->initItem(StoryItem::Root, tr("Story"), new StoryItem());
    }
    return m_rootItem;
}

/*
    Add Functions
    =============
*/

StoryItem *StoryTree::createItem(StoryItem::ItemType type, const QString &title, StoryItem *parent, int position) {
    StoryItem *item = new StoryItem();
    item->initItem(type, title, parent);
    if (parent->addChild(item, position)) {
        m_tree.insert(item->handle(), item);
        return item;
    }
    return nullptr;
}

/*
    XML Functions
    =============
*/

void StoryTree::toXML(const QString &ns, QXmlStreamWriter &xmlWriter) {

    if (!m_rootItem->isEmpty()) {
        xmlWriter.writeStartElement(ns, "story");
        xmlWriter.writeAttribute(ns, "handle", m_rootItem->handle());
        m_rootItem->toXml(ns, xmlWriter);
        xmlWriter.writeEndElement();
    }

    return;
}

} // namespace Collett
