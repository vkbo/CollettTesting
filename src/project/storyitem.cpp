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
    m_type = ItemType::Scene;
    m_cursorPos = 0;
    m_charCount = 0;
    m_wordCount = 0;
    m_paraCount = 0;
}

/*
    Methods
    =======
*/

void StoryItem::populateItem(ItemType type, const QString &title, const QString &handle) {
    m_empty = false;
    m_type = type;
    m_title = title;
    m_handle = handle;
}

void StoryItem::initItem(ItemType type, const QString &title) {
    QString newHandle = QUuid().createUuid().toString(QUuid::WithoutBraces);
    populateItem(type, title, newHandle);
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

int StoryItem::cursorPosition() const {
    return m_cursorPos;
}

int StoryItem::charCount() const {
    return m_charCount;
}

int StoryItem::wordCount() const {
    return m_wordCount;
}

int StoryItem::paraCount() const {
    return m_paraCount;
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

void StoryItem::setCharCount(int count) {
    if (count >= 0) {
        m_charCount = count;
    } else {
        m_charCount = 0;
    }
}

void StoryItem::setWordCount(int count) {
    if (count >= 0) {
        m_wordCount = count;
    } else {
        m_wordCount = 0;
    }
}

void StoryItem::setParaCount(int count) {
    if (count >= 0) {
        m_paraCount = count;
    } else {
        m_paraCount = 0;
    }
}

void StoryItem::setCounts(int cCount, int wCount, int pCount) {
    setCharCount(cCount);
    setWordCount(wCount);
    setParaCount(pCount);
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

    xmlWriter.writeStartElement(nsItm, "charCount");
    xmlWriter.writeCharacters(QString::number(m_charCount));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(nsItm, "wordCount");
    xmlWriter.writeCharacters(QString::number(m_wordCount));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(nsItm, "paraCount");
    xmlWriter.writeCharacters(QString::number(m_paraCount));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement(); // Close item
}

} // namespace Collett
