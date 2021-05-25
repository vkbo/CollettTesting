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

#ifndef COLITEM_H
#define COLITEM_H

#include <QString>
#include <QXmlStreamWriter>

namespace Collett {

class ColItem
{
public:
    enum ItemType {
        Chapter,
        Scene,
        Note,
    };

    ColItem(const QString &title, const QString &parent, const ItemType &type);
    ~ColItem() {};

    void toXml(const QString &nsCol, const QString &nsItm, QXmlStreamWriter &xmlWriter);
    static ColItem fromXml();

    // Getters
    QString  title() const;
    QString  handle() const;
    QString  parent() const;
    ItemType type() const;

    // Setters
    void setTitle(const QString &title);
    void setHandle(const QString &handle);
    void setParent(const QString &parent);
    void setType(const ItemType &type);

private:

    QString  m_title;
    QString  m_handle;
    QString  m_parent;
    ItemType m_type;

    int m_cursorPos;

};
} // namespace Collett

#endif // COLITEM_H
