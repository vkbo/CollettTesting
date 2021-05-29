/*
Collett – GUI Novel Tree Delegate Class
=======================================

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

#ifndef GUINOVELTREEDELEGATE_H
#define GUINOVELTREEDELEGATE_H

#include <QAbstractItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QPainter>
#include <QSize>
#include <QStyleOptionViewItem>

namespace Collett {

class GuiNovelTreeDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    GuiNovelTreeDelegate(QWidget *parent=nullptr);
    ~GuiNovelTreeDelegate() {};

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QFont m_typeFont;
    QFont m_titleFont;
    int m_typeHeight;
    int m_titleHeight;

};
} // namespace Collett

#endif // GUINOVELTREEDELEGATE_H
