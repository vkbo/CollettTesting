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

#include "documentblock.h"

#include <QString>
#include <QStringList>
#include <QChar>
#include <QTextBlock>
#include <QTextBlockFormat>
#include <QTextFragment>

#include <QDebug>

namespace Collett {

/*
    Public Methods
    ==============
*/

QString DocumentBlock::encodeQTextBlock(const QTextBlock &qBlock) {

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
    Private Methods
    ===============
*/

/*
    Parse an encoded line if text into a block format and a series of fragments
    with character formats. Also generate a plain text version of the line.
*/
DocumentBlock::Block DocumentBlock::decodeText(const QString &text) {

    Block block;

    if (!text.startsWith('[')) {
        block.valid = false;
        return block;
    }

    qsizetype endFmt = text.indexOf(']');
    if (endFmt < 0) {
        block.valid = false;
        return block;
    }

    QString blockFmt = text.first(endFmt+1);
    QString blockText = text.sliced(endFmt+1);

    // Parse block format
    block.styles = parseBlockFormat(blockFmt);
    if (!block.styles.valid) {
        block.valid = false;
        return block;
    }

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

        buffer.append(c);
        if (inFragment && c == '}' && buffer.startsWith("{f") && buffer.endsWith("{/f}")) {
            inFragment = false;
            textFrags.append(buffer);
            buffer = "";
        }
    }
    if (buffer != "") {
        textFrags.append(buffer);
    }

    block.fragments.clear();
    block.text.clear();
    for (const QString& textFrag : textFrags) {
        Fragment parsed = parseFragment(textFrag);
        block.fragments.append(parsed);
        block.text.append(parsed.text);
    }
    block.valid = true;

    qDebug() << "Block:" << blockFmt;
    qDebug() << "Text:" << blockText;
    qDebug() << "Fragments:" << textFrags;
    qDebug() << "Plain:" << block.text;

    return block;
}

/*
    Parse a colon separated string of codes for the block format of a document
    text block. The block must start with a text block code to be a valid text
    block.
*/
DocumentBlock::Styles DocumentBlock::parseBlockFormat(const QString &format) {

    Styles styles;

    QString fmtCore = format.sliced(1);
    fmtCore.chop(1);

    QStringList fmtBits = fmtCore.split(':', Qt::SkipEmptyParts);

    // A valid block contains at least one formatting key
    if (fmtBits.length() == 0) {
        styles.valid = false;
        return styles;
    }

    // The first key must be a text format key, otherwise this isn't a text block.
    if (fmtBits.length() > 0) {
        QString fmtBit = fmtBits.at(0);
        if (fmtBit == "TX") {
            styles.valid = true;
            styles.header = 0;
        } else if (fmtBit == "H1") {
            styles.valid = true;
            styles.header = 1;
        } else if (fmtBit == "H2") {
            styles.valid = true;
            styles.header = 2;
        } else if (fmtBit == "H3") {
            styles.valid = true;
            styles.header = 3;
        } else if (fmtBit == "H4") {
            styles.valid = true;
            styles.header = 4;
        } else {
            styles.valid = false;
            return styles;
        }
    }

    // Further keys are technically optional, but in a pre-defined order.
    // This is mstly to allow future extensions to the format.

    if (fmtBits.length() > 1) {
        QString fmtBit = fmtBits.at(1);
        if (fmtBit == "AL") {
            styles.alignemnt = Qt::AlignLeft;
        } else if (fmtBit == "AC") {
            styles.alignemnt = Qt::AlignCenter;
        } else if (fmtBit == "AR") {
            styles.alignemnt = Qt::AlignRight;
        } else if (fmtBit == "AJ") {
            styles.alignemnt = Qt::AlignJustify;
        } else {
            styles.alignemnt = Qt::AlignLeft;
        }
    }

    if (fmtBits.length() > 2) {
        styles.indent = fmtBits.at(2) == "I";
    }

    return styles;
}

/*
    Parse a text fragment and extract any formatting information that may exist
    in it. If there are no formatting tags, flag the fragment as plain text and
    return it as-is. If there are errors in the formatting tags, parse as much
    as possible and return the text with the tags. In principle, it should not
    be possible to lose any text if there are any errors.
*/
DocumentBlock::Fragment DocumentBlock::parseFragment(const QString &text) {

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
