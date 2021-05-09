/*
Collett – Document Exporter Class
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

#include "docexporter.h"
#include "linefmt.h"

#include <QStringList>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextFragment>
#include <QTextCharFormat>

namespace Collett {

/*
    Convert a QTextDocument into a list of strings, one for each paragraph.
    Each string starts with the paragraph format, and then follows the text of
    the paragraph with character formatting added in an html-like syntax.
*/
QStringList EditorDocExporter::toColletDoc() {
 
    QStringList docText;

    QTextBlock block = doc->firstBlock();

    while(block.isValid()) {

        DocLineFmt theFormat;

        auto blockFmt = block.blockFormat();

        theFormat.setBlockType(blockFmt.headingLevel());
        theFormat.setBlockAlignment(blockFmt.alignment());

        docText.append(theFormat.packFormat() + formatBlock(&block));
        block = block.next();
    }

    return docText;
}

QString EditorDocExporter::formatBlock(const QTextBlock *block) {

    QString fmtText = "";

    QTextBlock::Iterator blockIt = block->begin();
    for (; !blockIt.atEnd(); ++blockIt) {
        fmtText += formatFragment(blockIt.fragment());
    }

    return fmtText;
}

QString EditorDocExporter::formatFragment(const QTextFragment &fragment) {

    QString fragFmt = "";
    QString fmtText = fragment.text().replace('{', "\\{").replace('}', "\\}");

    QTextCharFormat chrFmt = fragment.charFormat();

    if (chrFmt.fontItalic()) fragFmt += "i";
    if (chrFmt.fontUnderline()) fragFmt += "u";
    if (chrFmt.fontWeight() > 500) fragFmt += "b";
    if (chrFmt.fontStrikeOut()) fragFmt += "s";

    if (fragFmt != "") {
        fmtText.prepend("{"+fragFmt+"}");
        fmtText.append("{/"+fragFmt+"}");
    }

    return fmtText;
}

} // namespace Collet
