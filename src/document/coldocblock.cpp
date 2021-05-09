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
        blockFragments.append(parseFragment(textFrag));
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

/*
    Internal Functions
    ==================
*/

ColDocBlock::Fragment ColDocBlock::parseFragment(const QString &text) {

    Fragment fragment;

    if (!text.startsWith("{f")) {
        fragment.valid = false;
        return fragment;
    }

    qsizetype endFmt = text.indexOf('}');
    if (endFmt < 0) {
        fragment.valid = false;
        return fragment;
    }

    fragment.text = text.sliced(endFmt+1);
    if (fragment.text.contains('\\')) {
        // Only replace escaped characters if there is a backslash
        fragment.text = fragment.text.replace("\\rc\\", "}").replace("\\lc\\", "{").replace("\\bs\\", "\\");
    }

    // Parse format flags
    for (int i=1; i<endFmt; ++i) {
        if (text.at(i) == 'b') {
            fragment.bold = true;
            continue;
        }
        if (text.at(i) == 'i') {
            fragment.italic = true;
            continue;
        }
        if (text.at(i) == 'u') {
            fragment.underline = true;
            continue;
        }
        if (text.at(i) == 's') {
            fragment.strikeout = true;
            continue;
        }
    }
    qDebug() << "Fragment Text:" << fragment.text;

    fragment.valid = false;

    return fragment;
}

} // namespace Collett
