/*
Collett – GUI Document Editor Class
===================================

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

#include "doceditor.h"
#include "linefmt.h"

#include <QDebug>
#include <QString>
#include <QTextEdit>
#include <QTextBlock>
#include <QStringList>

GuiDocEditor::GuiDocEditor(QWidget *parent) : QTextEdit(parent) {

    // Settings
    this->setAcceptRichText(true);

    this->setHtml(
        "<h1>Hello World</h1>"
        "<p>This is some text in a paragraph.</p>"
        "<p>And here is some more text in a second paragraph!</p>"
        "<p>Here we have some <b>bold</b> and <i>italic</i> text.</p>"
        "<p style='text-align: center;'><i>The End</i></p>"
    );

    return;
}

GuiDocEditor::~GuiDocEditor() {}

/*
 * Methods
 */

bool GuiDocEditor::saveDocument() {
    auto docText = this->getDocText();
    for (int i=0; i < docText.size(); ++i) {
        qInfo() << docText.at(i);
    }
    return true;
}

/*
 * Internal Functions
 */

QStringList GuiDocEditor::getDocText() {

    QStringList docText;

    auto *doc = this->document();
    QTextBlock block = doc->firstBlock();

    while(block.isValid()) {

        DocLineFmt theFormat;

        auto blockFmt = block.blockFormat();

        theFormat.setBlockType(blockFmt.headingLevel());
        theFormat.setBlockAlignment(blockFmt.alignment());

        docText.append(theFormat.packFormat() + block.text());
        block = block.next();
    }

    return docText;
}
