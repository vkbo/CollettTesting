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
#include <QTextBlock>
#include <QTextBlockFormat>
#include <QTextFragment>

#include <QDebug>

namespace Collett {

ColDocBlock::ColDocBlock() {
    blockValid = false;
}

QString ColDocBlock::encodeQTextBlock(const QTextBlock &qBlock) {

    QString blockText = "";
    if (!qBlock.isValid()) {
        return blockText;
    }

    // Block Format
    // ============

    QStringList blockFmt;
    QTextBlockFormat qBlockFmt = qBlock.blockFormat();

    // Encode Block Type
    int qHLevel = qBlockFmt.headingLevel();
    if (qHLevel > 0 && qHLevel < 5) {
        QString blockHeader;
        blockHeader.setNum(qHLevel);
        blockHeader.prepend('H');
        blockFmt.append(blockHeader);
    } else {
        blockFmt.append("TX");
    }

    // Encode Text Alignment
    switch (qBlockFmt.alignment() & 0x000f) {
        case Qt::AlignLeft:
            blockFmt.append("AL");
            break;
        case Qt::AlignHCenter:
            blockFmt.append("AC");
            break;
        case Qt::AlignRight:
            blockFmt.append("AR");
            break;
        case Qt::AlignJustify:
            blockFmt.append("AJ");
            break;
        default:
            blockFmt.append("AL");
            break;
    }

    // Encode Text Indent
    if (qBlockFmt.textIndent() > 0.0) {
        blockFmt.append("I");
    } else {
        blockFmt.append("O");
    }

    // Assemble Format
    blockText = blockFmt.join(":").prepend("[").append("]");

    // Block Text
    // ==========

    QTextBlock::Iterator blockIt = qBlock.begin();
    for (; !blockIt.atEnd(); ++blockIt) {

        QTextFragment qFrag = blockIt.fragment();
        QTextCharFormat chrFmt = qFrag.charFormat();

        QString fragFmt = "";
        QString fragTxt = qFrag.text();

        fragTxt.replace('\\', "\\bs\\");
        fragTxt.replace(QChar::LineSeparator, "\\br\\");
        fragTxt.replace('{', "\\lc\\");
        fragTxt.replace('}', "\\rc\\");

        if (chrFmt.fontWeight() > 500) fragFmt += "b";
        if (chrFmt.fontItalic()) fragFmt += "i";
        if (chrFmt.fontUnderline()) fragFmt += "u";
        if (chrFmt.fontStrikeOut()) fragFmt += "s";

        if (fragFmt != "") {
            fragTxt.prepend("{f"+fragFmt+"}");
            fragTxt.append("{/f}");
        }

        if (fragTxt != "") {
            blockText.append(fragTxt);
        }
    }

    return blockText;
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
        if (fmtBit == "TX") {
            block.header = 0;
        } else if (fmtBit == "H1") {
            block.header = 1;
        } else if (fmtBit == "H2") {
            block.header = 2;
        } else if (fmtBit == "H3") {
            block.header = 3;
        } else if (fmtBit == "H4") {
            block.header = 4;
        } else {
            block.header = 0;
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
        fragment.text.replace("\\rc\\", "}");
        fragment.text.replace("\\lc\\", "{");
        fragment.text.replace("\\br\\", QString(QChar::LineSeparator));
        fragment.text.replace("\\bs\\", "\\");
    }

    return fragment;
}

} // namespace Collett
