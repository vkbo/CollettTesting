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

#include "data.h"
#include "project.h"
#include "doceditor.h"
#include "docexporter.h"
#include "linefmt.h"

#include <QDebug>
#include <QString>
#include <QTextEdit>
#include <QTextBlock>
#include <QStringList>

namespace Collett {

GuiDocEditor::GuiDocEditor(QWidget *parent, ColData *_data)
    : QTextEdit(parent), mainData(_data)
{

    // Settings
    this->setAcceptRichText(true);

    return;
}

GuiDocEditor::~GuiDocEditor() {
    delete colDoc;
    hasDocument = false;
}

/*
    Document Functions
    ==================
*/

bool GuiDocEditor::openDocument(const QString handle) {

    colDoc = new ColDocument(mainData->getProject(), handle);
    hasDocument = true;

    this->setHtml(
        "<h1>Hello World</h1>"
        "<p>This is some text in a paragraph.</p>"
        "<p>And here is some {more} text in a second paragraph!</p>"
        "<p>Here we have some <b>bold</b> and <i>italic</i> text.</p>"
        "<p>This is <b>a <i>sentence <u>with <s>nested</s> formatting</u> in</i> the</b> middle.</p>"
        "<p style='text-align: center;'><i>The End</i></p>"
    );

    return true;
}

bool GuiDocEditor::saveDocument() {
    auto docText = this->toColletDoc();
    for (int i=0; i < docText.size(); ++i) {
        qInfo() << docText.at(i);
    }
    if (hasDocument) {
        colDoc->write(docText.join("\n"));
    }
    return true;
}

/*
 * Internal Functions
 */

QStringList GuiDocEditor::toColletDoc() {
    return EditorDocExporter(this->document()).toColletDoc();
}

} // namespace Collett
