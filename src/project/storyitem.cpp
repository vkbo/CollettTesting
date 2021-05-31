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

#include <QDomAttr>
#include <QDomElement>
#include <QDomNode>
#include <QJsonObject>
#include <QString>
#include <QUuid>
#include <QXmlStreamWriter>

namespace Collett {

StoryItem::StoryItem() {
    m_empty     = true;
    m_title     = "";
    m_handle    = "";
    m_type      = ItemType::Scene;
    m_itemCount = 0;
    m_cursorPos = 0;
    m_wordCount = 0;
}

/*
    Methods
    =======
*/

void StoryItem::populateItem(ItemType type, const QString &title, const QString &handle) {
    m_empty  = false;
    m_type   = type;
    m_title  = title;
    m_handle = handle;
}

void StoryItem::initItem(ItemType type, const QString &title) {
    QString newHandle = QUuid().createUuid().toString(QUuid::WithoutBraces);
    populateItem(type, title, newHandle);
}

QJsonObject StoryItem::toJson() {
    QJsonObject data;
    data.insert("title", m_title);
    data.insert("handle", m_handle);
    data.insert("type", typeForDisplay());
    data.insert("background", typeBackground());
    return data;
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

StoryItem::ItemType StoryItem::type() const {
    return m_type;
}

QString StoryItem::typeAsString() const {
    switch (m_type) {
        case ItemType::Title:
            return "title";
            break;
        case ItemType::Partition:
            return "partition";
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
    return "scene";
}

QString StoryItem::typeForDisplay() const {
    switch (m_type) {
        case ItemType::Title:
            return tr("Title Page");
            break;
        case ItemType::Partition:
            return tr("Part %1").arg(m_itemCount);
            break;
        case ItemType::Chapter:
            return tr("Chapter %1").arg(m_itemCount);
            break;
        case ItemType::Section:
            return tr("Section");
            break;
        case ItemType::Scene:
            return tr("Scene %1").arg(m_itemCount);
            break;
        case ItemType::Page:
            return tr("Page");
            break;
    }
    return tr("Scene");
}

QString StoryItem::typeBackground() const {
    switch (m_type) {
        case ItemType::Title:
            return "#00ff00";
            break;
        case ItemType::Partition:
            return "#00ff00";
            break;
        case ItemType::Chapter:
            return "#ff0000";
            break;
        case ItemType::Section:
            return "#ff0000";
            break;
        case ItemType::Scene:
            return "#0000ff";
            break;
        case ItemType::Page:
            return "#ffff00";
            break;
    }
    return "#ffffff";
}

int StoryItem::cursorPosition() const {
    return m_cursorPos;
}

int StoryItem::itemCount() const {
    return m_itemCount;
}

int StoryItem::wordCount() const {
    return m_wordCount;
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

void StoryItem::setType(ItemType type) {
    m_type = type;
}

void StoryItem::setCursorPosition(int position) {
    if (position >= 0) {
        m_cursorPos = position;
    } else {
        m_cursorPos = 0;
    }
}

void StoryItem::setItemCount(int count) {
    if (count > 0) {
        m_itemCount = count;
    } else {
        m_itemCount = 0;
    }
}

void StoryItem::setWordCount(int count) {
    if (count >= 0) {
        m_wordCount = count;
    } else {
        m_wordCount = 0;
    }
}

/*
    XML Functions
    =============
*/

void StoryItem::toXml(const QString &nsCol, const QString &nsItm, QXmlStreamWriter &xmlWriter) {

    if (m_empty) {
        return;
    }

    xmlWriter.writeStartElement(nsCol, "item");
    xmlWriter.writeAttribute(nsItm, "type", typeAsString());
    xmlWriter.writeAttribute(nsItm, "handle", handle());

    xmlWriter.writeStartElement(nsItm, "title");
    xmlWriter.writeCharacters(m_title);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(nsItm, "cursorPos");
    xmlWriter.writeCharacters(QString::number(m_cursorPos));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(nsItm, "wordCount");
    xmlWriter.writeCharacters(QString::number(m_wordCount));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement(); // Close item
}

void StoryItem::fromXml(const QString &nsCol, const QString &nsItm, QDomNode &node) {

    if (!node.isElement()) {
        return;
    }

    QDomElement eItem = node.toElement();

    // Minimal Required

    QDomAttr aType = eItem.attributeNodeNS(nsItm, "type");
    QDomAttr aHandle = eItem.attributeNodeNS(nsItm, "handle");

    if (aType.isNull() || aHandle.isNull()) {
        qWarning() << "Story item is missing type or handle, skipping";
    }

    ItemType type = ItemType::Scene;
    if (aType.value() == "title") {
        type = ItemType::Title;
    } else if (aType.value() == "partition") {
        type = ItemType::Partition;
    } else if (aType.value() == "chapter") {
        type = ItemType::Chapter;
    } else if (aType.value() == "section") {
        type = ItemType::Section;
    } else if (aType.value() == "scene") {
        type = ItemType::Scene;
    } else if (aType.value() == "page") {
        type = ItemType::Page;
    }

    populateItem(type, tr("Untitled"), aHandle.value());

    // Set Values

    QDomNode child = node.firstChild();
    while(!child.isNull()) {
        QDomElement element = child.toElement();
        if(!element.isNull()) {
            if (element.namespaceURI() == nsItm) {
                if (element.tagName() == QLatin1String("title")) {
                    setTitle(element.text());
                } else if (element.tagName() == QLatin1String("cursorPos")) {
                    setCursorPosition(element.text().toInt());
                } else if (element.tagName() == QLatin1String("wordCount")) {
                    setWordCount(element.text().toInt());
                }
            }
        }
        child = child.nextSibling();
    }

    return;
}

} // namespace Collett
