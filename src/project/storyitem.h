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

#ifndef COL_STORYITEM_H
#define COL_STORYITEM_H

#include <QJsonObject>
#include <QList>
#include <QString>
#include <QUuid>
#include <QXmlStreamWriter>
#include <QObject>

namespace Collett {

class StoryItem : public QObject
{
    Q_OBJECT

public:
    enum ItemType {Title, Partition, Chapter, Section, Scene, Page};

    StoryItem();
    ~StoryItem() {};

    void populateItem(ItemType type, const QString &title, const QString &handle);
    void initItem(ItemType type, const QString &title);

    void toXml(const QString &nsCol, const QString &nsItm, QXmlStreamWriter &xmlWriter);
    static StoryItem fromXml();

    QJsonObject toJson();

    bool isEmpty() {
        return m_empty;
    }

    // Getters
    QString  title() const;
    QString  handle() const;
    ItemType type() const;
    QString  typeAsString() const;
    QString  typeForDisplay() const;

    int cursorPosition() const;
    int itemCount() const;
    int charCount() const;
    int wordCount() const;
    int paraCount() const;

    // Setters
    void setTitle(const QString &title);
    void setHandle(const QString &handle);
    void setType(ItemType type);

    void setCursorPosition(int position);
    void setItemCount(int count);
    void setCharCount(int count);
    void setWordCount(int count);
    void setParaCount(int count);
    void setCounts(int cCount, int wCount, int pCount);

private:

    bool m_empty;

    QString  m_title;
    QString  m_handle;
    ItemType m_type;

    int m_itemCount;
    int m_cursorPos;
    int m_charCount;
    int m_wordCount;
    int m_paraCount;

};
} // namespace Collett

#endif // COL_STORYITEM_H
