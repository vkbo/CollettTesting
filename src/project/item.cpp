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

#include "item.h"

#include <QString>
#include <QUuid>
#include <QXmlStreamWriter>

namespace Collett {

ColItem::ColItem() {
    m_empty  = true;
    m_title  = "";
    m_handle = QUuid();
    m_type = ItemType::None;
    m_cursorPosition = 0;
}

void ColItem::populateItem(ItemType type, const QString &title, const QUuid &handle, ColItem *parent) {
    m_empty = false;
    m_type = type;
    m_title = title;
    m_handle = handle;
    m_parentItem = parent;
}

void ColItem::initItem(ItemType type, const QString &title, ColItem *parent) {
    QUuid newHandle = QUuid().createUuid();
    populateItem(type, title, newHandle, parent);
}

bool ColItem::addChild(ColItem *item, int position) {
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

QString ColItem::title() const {
    return m_title;
}

QString ColItem::handleAsString() const {
    return m_handle.toString(QUuid::WithoutBraces);
}

ColItem *ColItem::parent() const {
    return m_parentItem;
}

ColItem::ItemType ColItem::type() const {
    return m_type;
}

QString ColItem::typeAsString() const {
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
        case ItemType::Note:
            return "note";
            break;
    }
    return "none";
}

int ColItem::cursorPosition() {
    return m_cursorPosition;
}

/*
    Setters
    =======
*/

void ColItem::setTitle(const QString &title) {
    m_title = title;
}

void ColItem::setHandle(const QUuid &handle) {
    m_handle = handle;
}

void ColItem::setParent(ColItem *parent) {
    m_parentItem = parent;
}

void ColItem::setType(ItemType type) {
    m_type = type;
}

void ColItem::setCursorPosition(int position) {
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

void ColItem::toXml(const QString &ns, QXmlStreamWriter &xmlWriter) {

    xmlWriter.writeStartElement(ns, "title");
    xmlWriter.writeCharacters(m_title);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(ns, "cursorPos");
    xmlWriter.writeCharacters(QString().setNum(m_cursorPosition));
    xmlWriter.writeEndElement();

    if (!m_childItems.isEmpty()) {
        xmlWriter.writeStartElement(ns, "children");
        for (ColItem *item : m_childItems) {
            xmlWriter.writeStartElement(ns, typeAsString());
            xmlWriter.writeAttribute(ns, "handle", item->handleAsString());
            item->toXml(ns, xmlWriter);
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
    }
}

} // namespace Collett
