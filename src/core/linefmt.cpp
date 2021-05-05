/*
Collett – Line Format Class
===========================

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

#include "linefmt.h"

#include <QString>
#include <QStringList>

DocLineFmt::DocLineFmt() {
    blockTypeValue = 0;
    blockAlignValue = Qt::AlignLeft;
}

DocLineFmt::~DocLineFmt() {}

/*
 * Methods
 */

QString DocLineFmt::packFormat() {

    QStringList fmtText;

    QString fmtBlockType;
    fmtBlockType.setNum(blockTypeValue, 10);
    fmtBlockType.prepend("H");
    fmtText.append(fmtBlockType);

    switch (blockAlignValue) {
        case Qt::AlignLeft:
            fmtText.append("AL");
            break;
        case Qt::AlignCenter:
            fmtText.append("AC");
            break;
        case Qt::AlignRight:
            fmtText.append("AR");
            break;
        case Qt::AlignJustify:
            fmtText.append("AJ");
            break;
        default:
            fmtText.append("AL");
            break;
    }

    return fmtText.join(":").prepend("[").append("]");
}

/*
 * Setters
 */

void DocLineFmt::setBlockType(int blockType) {
    if (blockType >= 0 && blockType <= 4) {
        blockTypeValue = blockType;
    } else {
        blockTypeValue = 0;
    }
}

void DocLineFmt::setBlockAlignment(Qt::Alignment alignFlag) {
    blockAlignValue = alignFlag;
}
