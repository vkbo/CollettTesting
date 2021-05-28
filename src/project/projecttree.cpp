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
#include <QString>
#include <QUuid>
#include <QXmlStreamWriter>

namespace Collett {

ColProjectTree::ColProjectTree(QObject *parent)
    : QObject(parent)
{
    m_storyRoot = new ColItem();
    m_notesRoot = new ColItem();
}

ColProjectTree::~ColProjectTree() {
    delete m_storyRoot;
    delete m_notesRoot;
}

/*
    Access Methods
    ==============
*/

ColItem *ColProjectTree::itemWithHandle(const QString &handle) {
    return m_tree.value(handle, nullptr);
}

int ColProjectTree::count() const {
    return m_tree.count();
}

/*
    Root Items
    ==========
*/

ColItem *ColProjectTree::storyRootItem() {
    if (m_storyRoot->isEmpty()) {
        m_storyRoot->initItem(ColItem::Root, tr("Story"), new ColItem());
    }
    return m_storyRoot;
}

ColItem *ColProjectTree::notesRootItem() {
    if (m_notesRoot->isEmpty()) {
        m_notesRoot->initItem(ColItem::Root, tr("Notes"), new ColItem());
    }
    return m_notesRoot;
}

/*
    Add Functions
    =============
*/

ColItem *ColProjectTree::createItem(ColItem::ItemType type, const QString &title, ColItem *parent, int position) {
    ColItem *item = new ColItem();
    item->initItem(type, title, parent);
    parent->addChild(item, position);
    return item;
}

/*
    XML Functions
    =============
*/

void ColProjectTree::toXML(const QString &ns, QXmlStreamWriter &xmlWriter) {

    if (!m_storyRoot->isEmpty()) {
        xmlWriter.writeStartElement(ns, "story");
        xmlWriter.writeAttribute(ns, "handle", m_storyRoot->handleAsString());
        m_storyRoot->toXml(ns, xmlWriter);
        xmlWriter.writeEndElement();
    }

    if (!m_notesRoot->isEmpty()) {
        xmlWriter.writeStartElement(ns, "notes");
        xmlWriter.writeAttribute(ns, "handle", m_notesRoot->handleAsString());
        m_notesRoot->toXml(ns, xmlWriter);
        xmlWriter.writeEndElement();
    }

    return;
}

} // namespace Collett
