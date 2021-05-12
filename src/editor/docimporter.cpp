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

    cursor.beginEditBlock();
    for (const QString& line : rawText) {
        ColDocBlock newBlock;
        newBlock.unpackText(line);
        if (!newBlock.isValid()) {
            qWarning() << "Invalid block encountered";
            continue;
        }

        QTextCharFormat defaultFmt(cursor.charFormat());

        for (const ColDocBlock::Fragment& blockFrag : newBlock.fragments()) {
            if (blockFrag.plain) {
                cursor.insertText(blockFrag.text, defaultFmt);
            } else {
                auto insFmt = defaultFmt;
                insFmt.setFontWeight(blockFrag.bold ? 700 : 400);
                insFmt.setFontItalic(blockFrag.italic);
                insFmt.setFontUnderline(blockFrag.underline);
                insFmt.setFontStrikeOut(blockFrag.strikeout);
                cursor.insertText(blockFrag.text, insFmt);
            }
        }
        cursor.insertBlock();
    }
    cursor.endEditBlock();

    return;
}

} // namespace Collett
