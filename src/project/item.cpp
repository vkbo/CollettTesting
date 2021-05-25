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

ColItem::ColItem(const QString &title, const QString &parent, const ItemType &type){

    m_title  = title;
    m_handle = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_parent = parent;
    m_type   = type;

}

void ColItem::toXml(const QString &nsCol, const QString &nsItm, QXmlStreamWriter &xmlWriter) {

    xmlWriter.writeStartElement(nsCol, "item");
    xmlWriter.writeAttribute(nsItm, "handle", m_handle);
    xmlWriter.writeAttribute(nsItm, "parent", m_parent);

    xmlWriter.writeStartElement(nsItm, "title");
    xmlWriter.writeCharacters(m_title);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(nsItm, "type");
    switch (m_type) {
        case ItemType::Chapter:
            xmlWriter.writeCharacters("CHAPTER");
            break;
        case ItemType::Scene:
            xmlWriter.writeCharacters("SCENE");
            break;
        case ItemType::Note:
            xmlWriter.writeCharacters("NOTE");
            break;
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(nsItm, "cursorPos");
    xmlWriter.writeCharacters(QString().setNum(m_cursorPos));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement(); // Close: item
}

} // namespace Collett
