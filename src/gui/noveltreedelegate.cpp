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

#include "noveltreedelegate.h"
#include "storyitem.h"

#include <QAbstractItemDelegate>
#include <QApplication>
#include <QFont>
#include <QFontMetrics>
#include <QJsonObject>
#include <QModelIndex>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QSize>
#include <QStyleOptionViewItem>

namespace Collett {

GuiNovelTreeDelegate::GuiNovelTreeDelegate(QWidget *parent)
    : QAbstractItemDelegate(parent)
{
    m_typeFont = qApp->font();
    m_titleFont = qApp->font();

    m_typeFont.setPointSizeF(0.8*m_titleFont.pointSizeF());
    m_typeFont.setWeight(QFont::Bold);

    m_titleHeight = QFontMetrics(m_titleFont).height();
    m_typeHeight = QFontMetrics(m_typeFont).height();
}

void GuiNovelTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    QJsonObject data = index.model()->data(index, Qt::DisplayRole).toJsonObject();

    QColor col(data.value("background").toString());
    if (option.state & QStyle::State_Selected) {
        col.setAlpha(108);
        painter->fillRect(option.rect, QBrush(col, Qt::SolidPattern));
    } else {
        col.setAlpha(24);
        painter->fillRect(option.rect, QBrush(col, Qt::SolidPattern));
    }

    painter->save();

    int y = option.rect.y();
    int w = option.rect.width();

    int y1 = y + 2;
    int y2 = y1 + 2 + m_typeHeight;
    int y3 = y2 + 2 + m_titleHeight;

    QRect pRect1(2, y1, w, m_typeHeight);
    painter->setFont(m_typeFont);
    painter->drawText(pRect1, Qt::TextSingleLine, data.value("type").toString());

    QRect pRect2(2, y2, w, m_titleHeight);
    painter->setFont(m_titleFont);
    painter->drawText(pRect2, Qt::TextSingleLine, data.value("title").toString());

    QPen pen = painter->pen();
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    painter->drawLine(0, y3, w, y3);

    painter->restore();
}

QSize GuiNovelTreeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(option.rect.width(), m_typeHeight + m_titleHeight + 7);
}

} // namespace Collett
