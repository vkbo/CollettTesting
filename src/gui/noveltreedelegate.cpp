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

#include <QApplication>
#include <QAbstractItemDelegate>
#include <QJsonObject>
#include <QModelIndex>
#include <QObject>
#include <QPainter>
#include <QSize>
#include <QStyleOptionViewItem>
#include <QFont>
#include <QRect>
#include <QFontMetrics>

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

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    painter->save();

    QJsonObject data = index.model()->data(index, Qt::DisplayRole).toJsonObject();
    int y = option.rect.y();
    int w = option.rect.width();

    QRect pRect1(2, y+2, w, m_typeHeight);
    painter->setFont(m_typeFont);
    painter->drawText(pRect1, Qt::TextSingleLine, data.value("type").toString());

    QRect pRect2(2, y+4+m_typeHeight, w, m_titleHeight);
    painter->setFont(m_titleFont);
    painter->drawText(pRect2, Qt::TextSingleLine, data.value("title").toString());

    painter->restore();
}

QSize GuiNovelTreeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(option.rect.width(), m_typeHeight + m_titleHeight + 6);
}

} // namespace Collett
