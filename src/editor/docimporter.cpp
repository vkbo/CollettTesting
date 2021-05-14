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
#include "doceditor.h"
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

void EditorDocImporter::import(const GuiDocEditor::DocFormat &format) {

    cursor.beginEditBlock();
    for (const QString& line : rawText) {
        ColDocBlock newBlock;
        newBlock.unpackText(line);
        if (!newBlock.isValid()) {
            qWarning() << "Invalid block encountered";
            continue;
        }

        QTextBlockFormat textBlockFmt = format.blockDefault;
        QTextCharFormat textCharFmt = format.charDefault;

        ColDocBlock::Block lineFmt = newBlock.blockStyle();
        switch (lineFmt.type) {
            case ColDocBlock::Paragraph:
                textBlockFmt = format.blockParagraph;
                textCharFmt = format.charParagraph;
                break;

            case ColDocBlock::Header1:
                textBlockFmt = format.blockHeader1;
                textCharFmt = format.charHeader1;
                break;

            case ColDocBlock::Header2:
                textBlockFmt = format.blockHeader2;
                textCharFmt = format.charHeader2;
                break;

            case ColDocBlock::Header3:
                textBlockFmt = format.blockHeader3;
                textCharFmt = format.charHeader3;
                break;

            case ColDocBlock::Header4:
                textBlockFmt = format.blockHeader4;
                textCharFmt = format.charHeader4;
                break;

            case ColDocBlock::KeyWord:
                break;

            case ColDocBlock::BlockQuote:
                break;

            case ColDocBlock::Comment:
                break;

            case ColDocBlock::Title:
                break;
        }

        textBlockFmt.setAlignment(lineFmt.alignemnt);
        if (lineFmt.indent) {
            textBlockFmt.setTextIndent(format.blockIndent);
        }

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
