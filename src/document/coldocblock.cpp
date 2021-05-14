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

    auto endFmt = text.indexOf(']');
    if (endFmt < 0) {
        blockValid = false;
        return;
    }

    QString blockFmt = text.first(endFmt+1);
    QString blockText = text.sliced(endFmt+1);

    // Parse block format
    blockStyles = parseBlockFormat(blockFmt);

    // Parse block text
    QStringList textFrags;
    QString buffer;
    bool inFragment = false;
    for (const QChar& c : blockText) {

        if (!inFragment && c == '{') {
            inFragment = true;
            if (buffer != "") {
                textFrags.append(buffer);
                buffer = "";
            }
        }

        buffer += c;
        if (inFragment && c == '}' && buffer.startsWith("{f") && buffer.endsWith("{/f}")) {
            inFragment = false;
            textFrags.append(buffer);
            buffer = "";
        }
    }
    if (buffer != "") {
        textFrags.append(buffer);
    }

    qDebug() << "Format:" << blockFmt;
    qDebug() << "Text:" << blockText;
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

    switch (blockStyles.type) {
        case (ColDocBlock::Title):
            fmtText.append("TT");
            break;
        case (ColDocBlock::Header1):
            fmtText.append("H1");
            break;
        case (ColDocBlock::Header2):
            fmtText.append("H2");
            break;
        case (ColDocBlock::Header3):
            fmtText.append("H3");
            break;
        case (ColDocBlock::Header4):
            fmtText.append("H4");
            break;
        case (ColDocBlock::Paragraph):
            fmtText.append("PP");
            break;
        case (ColDocBlock::BlockQuote):
            fmtText.append("BQ");
            break;
        case (ColDocBlock::KeyWord):
            fmtText.append("KW");
            break;
        case (ColDocBlock::Comment):
            fmtText.append("CC");
            break;
        default:
            fmtText.append("PP");
            break;
    }

    switch (blockStyles.alignemnt) {
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

    if (blockStyles.indent) {
        fmtText.append("I");
    } else {
        fmtText.append("O");
    }

    return fmtText.join(":").prepend("[").append("]");
}

/*
    Setters
    =======
*/

void ColDocBlock::setBlockType(ColDocBlock::BlockType blockType) {
    blockStyles.type = blockType;
}

void ColDocBlock::setBlockAlignment(Qt::Alignment alignFlag) {
    blockStyles.alignemnt = alignFlag;
}

/*
    Internal Functions
    ==================
*/

ColDocBlock::Block ColDocBlock::parseBlockFormat(const QString &format) {

    Block block;

    QString fmtCore = format.sliced(1);
    fmtCore.chop(1);

    QStringList fmtBits = fmtCore.split(':', Qt::SkipEmptyParts);

    if (fmtBits.length() > 0) {
        QString fmtBit = fmtBits.at(0);
        if (fmtBit == "PP") {
            block.type = BlockType::Paragraph;
        } else if (fmtBit == "H1") {
            block.type = BlockType::Header1;
        } else if (fmtBit == "H2") {
            block.type = BlockType::Header2;
        } else if (fmtBit == "H3") {
            block.type = BlockType::Header3;
        } else if (fmtBit == "H4") {
            block.type = BlockType::Header4;
        } else if (fmtBit == "KW") {
            block.type = BlockType::KeyWord;
        } else if (fmtBit == "BQ") {
            block.type = BlockType::BlockQuote;
        } else if (fmtBit == "CC") {
            block.type = BlockType::Comment;
        } else if (fmtBit == "TT") {
            block.type = BlockType::Title;
        } else {
            block.type = BlockType::Paragraph;
        }
    }

    if (fmtBits.length() > 1) {
        QString fmtBit = fmtBits.at(1);
        if (fmtBit == "AL") {
            block.alignemnt = Qt::AlignLeft;
        } else if (fmtBit == "AC") {
            block.alignemnt = Qt::AlignCenter;
        } else if (fmtBit == "AR") {
            block.alignemnt = Qt::AlignRight;
        } else if (fmtBit == "AJ") {
            block.alignemnt = Qt::AlignJustify;
        } else {
            block.alignemnt = Qt::AlignLeft;
        }
    }

    if (fmtBits.length() > 2) {
        block.indent = fmtBits.at(2) == "I";
    }

    return block;
}

/*
    Parse a text fragment and extract any formatting information that may exist
    in it. If there are no formatting tags, flag the fragment as plain text and
    return it as-is. If there are errors in the formatting tags, parse as much
    as possible and return the text with the tags. In principle, it should not
    be possible to lose any text if there are any errors.
*/
ColDocBlock::Fragment ColDocBlock::parseFragment(const QString &text) {

    Fragment fragment;

    // Check if we have an unformatted or formatted fragment
    if (!text.startsWith("{") && !text.endsWith("}") ) {

        // It is unformatted, so we keep it as-is
        fragment.plain = true;
        fragment.valid = true;
        fragment.text = text;

    } else {

        // We have a block with formatting, check that it is valid
        fragment.plain = false;

        // It must have open and close tags to be valid
        if (text.startsWith("{f") && text.endsWith("{/f}") ) {
            fragment.valid = true;
        } else {
            fragment.valid = false;
        }

        // Also check that the opening formatting tag is closed
        auto endFmt = text.indexOf('}');
        if (endFmt < 0 || endFmt > text.length() - 5) {
            fragment.valid = false;
        }

        // If the fragment is a valid format fragment, parse it,
        // otherwise just return the text as-is
        if (fragment.valid) {

            // Remove the tags
            fragment.text = text.sliced(endFmt+1);
            fragment.text.chop(4);

            // Parse format flags
            for (int i=1; i<endFmt; ++i) {
                if (text.at(i) == 'f') {
                    continue;
                } else if (text.at(i) == 'b') {
                    fragment.bold = true;
                } else if (text.at(i) == 'i') {
                    fragment.italic = true;
                } else if (text.at(i) == 'u') {
                    fragment.underline = true;
                } else if (text.at(i) == 's') {
                    fragment.strikeout = true;
                } else {
                    fragment.text = text;
                    break;
                }
            }
        } else {
            fragment.text = text;
        }
    }

    // If there are any backslashes in the fragment text, run the replacements
    if (fragment.text.contains('\\')) {
        fragment.text.replace("\\rc\\", "}").replace("\\lc\\", "{").replace("\\bs\\", "\\");
    }

    return fragment;
}

} // namespace Collett
