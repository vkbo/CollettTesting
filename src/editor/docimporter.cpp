/*
Collett – Document Importer Class
=================================

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

#include "docimporter.h"
#include "coldocblock.h"

#include <QTextDocument>
#include <QString>
#include <QStringList>
#include <QTextCursor>
#include <QTextCharFormat>

#include <QDebug>

namespace Collett {

EditorDocImporter::EditorDocImporter(QTextDocument *_doc, const QStringList &content) : doc(_doc) {

    cursor = QTextCursor(doc);
    rawText = content;

}

/*
    Methods
    =======
*/

void EditorDocImporter::import() {

    QTextCharFormat  defaultCharFmt(cursor.charFormat());
    QTextBlockFormat defaultBlockFmt(cursor.blockFormat());

    qreal defaultFontSize = 13.0;
    qreal defaultLineHeight = 1.15;
    qreal defaultTopMargin = 0.5*defaultFontSize;
    qreal defaultBottomMargin = 0.5*defaultFontSize;

    qreal header1FontSize = 2.2*defaultFontSize;
    qreal header2FontSize = 1.9*defaultFontSize;
    qreal header3FontSize = 1.6*defaultFontSize;
    qreal header4FontSize = 1.3*defaultFontSize;

    qreal headerBottomMargin = 0.7*defaultFontSize;

    defaultCharFmt.setFontPointSize(defaultFontSize);
    defaultBlockFmt.setLineHeight(defaultLineHeight, QTextBlockFormat::SingleHeight);
    defaultBlockFmt.setTopMargin(defaultTopMargin);
    defaultBlockFmt.setBottomMargin(defaultBottomMargin);

    bool firstPara = true;

    cursor.beginEditBlock();
    for (const QString& line : rawText) {
        ColDocBlock newBlock;
        newBlock.unpackText(line);
        if (!newBlock.isValid()) {
            qWarning() << "Invalid block encountered";
            continue;
        }

        QTextBlockFormat textBlockFmt = defaultBlockFmt;
        QTextCharFormat  textCharFmt = defaultCharFmt;

        ColDocBlock::Block lineFmt = newBlock.blockStyle();
        switch (lineFmt.type) {
            case ColDocBlock::Header1:
                textBlockFmt.setHeadingLevel(1);
                textBlockFmt.setTopMargin(header1FontSize);
                textBlockFmt.setBottomMargin(headerBottomMargin);
                textCharFmt.setFontPointSize(header1FontSize);
                firstPara = true;
                break;

            case ColDocBlock::Header2:
                textBlockFmt.setHeadingLevel(2);
                textBlockFmt.setTopMargin(header2FontSize);
                textBlockFmt.setBottomMargin(headerBottomMargin);
                textCharFmt.setFontPointSize(header2FontSize);
                firstPara = true;
                break;

            case ColDocBlock::Header3:
                textBlockFmt.setHeadingLevel(3);
                textBlockFmt.setTopMargin(header3FontSize);
                textBlockFmt.setBottomMargin(headerBottomMargin);
                textCharFmt.setFontPointSize(header3FontSize);
                firstPara = true;
                break;

            case ColDocBlock::Header4:
                textBlockFmt.setHeadingLevel(4);
                textBlockFmt.setTopMargin(header4FontSize);
                textBlockFmt.setBottomMargin(headerBottomMargin);
                textCharFmt.setFontPointSize(header4FontSize);
                firstPara = true;
                break;

            case ColDocBlock::Paragraph:
                textBlockFmt.setHeadingLevel(0);
                if (!firstPara) {
                    textBlockFmt.setTextIndent(2.0*defaultFontSize);
                }
                firstPara = false;
                break;

            default:
                textBlockFmt.setHeadingLevel(0);
                break;
        }

        textBlockFmt.setAlignment(lineFmt.alignemnt);
        cursor.setBlockFormat(textBlockFmt);

        for (const ColDocBlock::Fragment& blockFrag : newBlock.fragments()) {
            if (blockFrag.plain) {
                cursor.insertText(blockFrag.text, textCharFmt);
            } else {
                auto textFragFmt = textCharFmt;
                textFragFmt.setFontWeight(blockFrag.bold ? 700 : 400);
                textFragFmt.setFontItalic(blockFrag.italic);
                textFragFmt.setFontUnderline(blockFrag.underline);
                textFragFmt.setFontStrikeOut(blockFrag.strikeout);
                cursor.insertText(blockFrag.text, textFragFmt);
            }
        }
        cursor.insertBlock();
    }
    cursor.endEditBlock();

    return;
}

} // namespace Collett
