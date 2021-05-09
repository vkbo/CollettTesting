/*
Collett – Collett Document Block Class
======================================

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

#include "coldocblock.h"
#include "coldocfragment.h"

#include <QString>
#include <QStringList>
#include <QChar>

#include <QDebug>

namespace Collett {

ColDocBlock::ColDocBlock() {

    blockValid = false;
    blockTypeValue = 0;
    blockAlignValue = Qt::AlignLeft;

}

/*
    Methods
    =======
*/

void ColDocBlock::unpackText(const QString &text) {

    if (!text.startsWith('[')) {
        blockValid = false;
        return;
    }

    qsizetype endFmt = text.indexOf(']');
    if (endFmt < 0) {
        blockValid = false;
        return;
    }

    QString blockFmt = text.first(endFmt+1);
    QString blockText = text.sliced(endFmt+1);

    qDebug() << "Format:" << blockFmt;
    qDebug() << "Text:" << blockText;

    QStringList textFrags = blockText.split("{/f}", Qt::SkipEmptyParts);
    qDebug() << "Fragments:" << textFrags;

    blockFragments.clear();
    for (const QString& textFrag : textFrags) {
        blockFragments.append(ColDocFragment(textFrag));
    }

    blockValid = true;

    return;
}

QString ColDocBlock::packText() {

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
    Setters
    =======
*/

void ColDocBlock::setBlockType(int blockType) {
    if (blockType >= 0 && blockType <= 4) {
        blockTypeValue = blockType;
    } else {
        blockTypeValue = 0;
    }
}

void ColDocBlock::setBlockAlignment(Qt::Alignment alignFlag) {
    blockAlignValue = alignFlag;
}

} // namespace Collett
