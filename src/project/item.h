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

#include <QList>
#include <QString>
#include <QUuid>
#include <QXmlStreamWriter>

namespace Collett {

class ColItem
{
public:
    enum ItemType {
        None = 0,
        Root = 1,
        Chapter = 2,
        Section = 3,
        Scene = 4,
        Page = 5,
        Note = 6,
    };

    ColItem();
    ~ColItem() {};

    void populateItem(ItemType type, const QString &title, const QUuid &handle, ColItem *parent);
    void initItem(ItemType type, const QString &title, ColItem *parent);
    bool addChild(ColItem *item, int position=-1);

    void toXml(const QString &ns, QXmlStreamWriter &xmlWriter);
    static ColItem fromXml();

    bool isEmpty() {
        return m_empty;
    }

    // Getters
    QString  title() const;
    QString  handleAsString() const;
    ColItem *parent() const;
    ItemType type() const;
    QString  typeAsString() const;
    int      cursorPosition();

    // Setters
    void setTitle(const QString &title);
    void setHandle(const QUuid &handle);
    void setParent(ColItem *parent);
    void setType(ItemType type);
    void setCursorPosition(int position);

private:

    QList<ColItem *> m_childItems;
    ColItem *m_parentItem;

    bool m_empty;

    QString  m_title;
    QUuid    m_handle;
    ItemType m_type;

    int m_cursorPosition;

};
} // namespace Collett

#endif // COLITEM_H
