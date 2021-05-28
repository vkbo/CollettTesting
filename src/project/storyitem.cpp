/*
Collett – Project Item Class
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

#include "storyitem.h"

#include <QString>
#include <QUuid>
#include <QXmlStreamWriter>

namespace Collett {

StoryItem::StoryItem() {
    m_empty  = true;
    m_title  = "";
    m_handle = "";
    m_type = ItemType::None;
    m_cursorPosition = 0;
}

void StoryItem::populateItem(ItemType type, const QString &title, const QString &handle, StoryItem *parent) {
    m_empty = false;
    m_type = type;
    m_title = title;
    m_handle = handle;
    m_parentItem = parent;
}

void StoryItem::initItem(ItemType type, const QString &title, StoryItem *parent) {
    QString newHandle = QUuid().createUuid().toString(QUuid::WithoutBraces);
    populateItem(type, title, newHandle, parent);
}

bool StoryItem::addChild(StoryItem *item, int position) {
    if (m_type != ItemType::Root && m_type != ItemType::Chapter && m_type != ItemType::Section) {
        return false;
    }

    if (position < 0) {
        m_childItems.append(item);
        return true;
    } else if (position >= 0 && position <= m_childItems.size()) {
        m_childItems.insert(position, item);
        return true;
    } else {
        return false;
    }
}

/*
    Getters
    =======
*/

QString StoryItem::title() const {
    return m_title;
}

QString StoryItem::handle() const {
    return m_handle;
}

StoryItem *StoryItem::parent() const {
    return m_parentItem;
}

StoryItem::ItemType StoryItem::type() const {
    return m_type;
}

QString StoryItem::typeAsString() const {
    switch (m_type) {
        case ItemType::None:
            return "none";
            break;
        case ItemType::Root:
            return "root";
            break;
        case ItemType::Chapter:
            return "chapter";
            break;
        case ItemType::Section:
            return "section";
            break;
        case ItemType::Scene:
            return "scene";
            break;
        case ItemType::Page:
            return "page";
            break;
    }
    return "none";
}

int StoryItem::cursorPosition() {
    return m_cursorPosition;
}

/*
    Setters
    =======
*/

void StoryItem::setTitle(const QString &title) {
    m_title = title;
}

void StoryItem::setHandle(const QString &handle) {
    m_handle = handle;
}

void StoryItem::setParent(StoryItem *parent) {
    m_parentItem = parent;
}

void StoryItem::setType(ItemType type) {
    m_type = type;
}

void StoryItem::setCursorPosition(int position) {
    if (position >= 0) {
        m_cursorPosition = position;
    } else {
        m_cursorPosition = 0;
    }
}

/*
    XML Functions
    =============
*/

void StoryItem::toXml(const QString &ns, QXmlStreamWriter &xmlWriter) {

    xmlWriter.writeStartElement(ns, "title");
    xmlWriter.writeCharacters(m_title);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(ns, "cursorPos");
    xmlWriter.writeCharacters(QString().setNum(m_cursorPosition));
    xmlWriter.writeEndElement();

    if (!m_childItems.isEmpty()) {
        xmlWriter.writeStartElement(ns, "children");
        for (StoryItem *item : m_childItems) {
            xmlWriter.writeStartElement(ns, typeAsString());
            xmlWriter.writeAttribute(ns, "handle", item->handle());
            item->toXml(ns, xmlWriter);
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
    }
}

} // namespace Collett
