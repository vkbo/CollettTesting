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
#include "documentblock.h"

#include <QDebug>
#include <QString>
#include <QTextEdit>
#include <QTextBlock>
#include <QStringList>
#include <QTextDocument>
#include <QTextCursor>

namespace Collett {

GuiDocEditor::GuiDocEditor(QWidget *parent)
    : QTextEdit(parent)
{
    mainData = CollettData::instance();

    // Settings
    this->setAcceptRichText(true);

    // Set up formats
    // ==============

    QTextCharFormat  defaultCharFmt;
    QTextBlockFormat defaultBlockFmt;

    qreal defaultFontSize = 13.0;
    qreal defaultLineHeight = 1.15;
    qreal defaultTopMargin = 0.5*defaultFontSize;
    qreal defaultBottomMargin = 0.5*defaultFontSize;

    qreal header1FontSize = 2.2*defaultFontSize;
    qreal header2FontSize = 1.9*defaultFontSize;
    qreal header3FontSize = 1.6*defaultFontSize;
    qreal header4FontSize = 1.3*defaultFontSize;

    qreal headerBottomMargin = 0.7*defaultFontSize;

    defaultBlockFmt.setHeadingLevel(0);
    defaultBlockFmt.setLineHeight(defaultLineHeight, QTextBlockFormat::SingleHeight);
    defaultBlockFmt.setTopMargin(defaultTopMargin);
    defaultBlockFmt.setBottomMargin(defaultBottomMargin);
    defaultBlockFmt.setTextIndent(0.0);

    defaultCharFmt.setFontPointSize(defaultFontSize);

    // Values
    docFormat.blockIndent = 2.0*defaultFontSize;

    // Default
    docFormat.blockDefault = defaultBlockFmt;
    docFormat.charDefault = defaultCharFmt;

    // Paragraph
    docFormat.blockParagraph = defaultBlockFmt;
    docFormat.charParagraph = defaultCharFmt;

    // Header 1
    docFormat.blockHeader1 = defaultBlockFmt;
    docFormat.blockHeader1.setHeadingLevel(1);
    docFormat.blockHeader1.setTopMargin(header1FontSize);
    docFormat.blockHeader1.setBottomMargin(headerBottomMargin);

    docFormat.charHeader1 = defaultCharFmt;
    docFormat.charHeader1.setFontPointSize(header1FontSize);

    // Header 2
    docFormat.blockHeader2 = defaultBlockFmt;
    docFormat.blockHeader2.setHeadingLevel(2);
    docFormat.blockHeader2.setTopMargin(header2FontSize);
    docFormat.blockHeader2.setBottomMargin(headerBottomMargin);

    docFormat.charHeader2 = defaultCharFmt;
    docFormat.charHeader2.setFontPointSize(header2FontSize);

    // Header 3
    docFormat.blockHeader3 = defaultBlockFmt;
    docFormat.blockHeader3.setHeadingLevel(3);
    docFormat.blockHeader3.setTopMargin(header3FontSize);
    docFormat.blockHeader3.setBottomMargin(headerBottomMargin);

    docFormat.charHeader3 = defaultCharFmt;
    docFormat.charHeader3.setFontPointSize(header3FontSize);

    // Header 4
    docFormat.blockHeader4 = defaultBlockFmt;
    docFormat.blockHeader4.setHeadingLevel(4);
    docFormat.blockHeader4.setTopMargin(header4FontSize);
    docFormat.blockHeader4.setBottomMargin(headerBottomMargin);

    docFormat.charHeader4 = defaultCharFmt;
    docFormat.charHeader4.setFontPointSize(header4FontSize);

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

    colDoc = new DocumentStore(mainData->project(), handle);
    hasDocument = true;

    this->setColletDoc(colDoc->paragraphs());

    // this->setHtml(
    //     "<h1>Hello World</h1>"
    //     "<p>This is some text in a paragraph.</p>"
    //     "<p>And here is some {more} text in a second paragraph!</p>"
    //     "<p>Here we have some <b>bold</b> and <i>italic</i> text.</p>"
    //     "<p>This is <b>a <i>sentence <u>with <s>nested</s> formatting</u> in</i> the</b> middle.</p>"
    //     "<p style='text-align: center;'><i>The End</i></p>"
    // );

    return true;
}

bool GuiDocEditor::saveDocument() {
    QStringList docText = this->toColletDoc();
    for (int i=0; i < docText.size(); ++i) {
        qInfo() << docText.at(i);
    }
    if (hasDocument) {
        colDoc->write(docText.join("\n"));
    }
    return true;
}

/*
    Internal Functions
    ==================
*/

/*
    Decode Document
    ===============
    Populate the editor's QTextDocument by decoding a list of QStrings using
    the DocumentBlock class.
*/
void GuiDocEditor::setColletDoc(const QStringList &content) {

    QTextDocument *doc = this->document();
    QTextCursor cursor = QTextCursor(doc);
    bool isFirst = true;

    doc->setUndoRedoEnabled(false);
    doc->clear();

    cursor.beginEditBlock();
    for (const QString& line : content) {
        DocumentBlock newBlock;
        newBlock.unpackText(line);
        if (!newBlock.isValid()) {
            qWarning() << "Invalid block encountered";
            continue;
        }

        if (isFirst) {
            isFirst = false;
        } else {
            cursor.insertBlock();
        }

        QTextBlockFormat textBlockFmt = docFormat.blockDefault;
        QTextCharFormat textCharFmt = docFormat.charDefault;

        DocumentBlock::Block lineFmt = newBlock.blockStyle();
        switch (lineFmt.header) {
            case 1:
                textBlockFmt = docFormat.blockHeader1;
                textCharFmt = docFormat.charHeader1;
                break;

            case 2:
                textBlockFmt = docFormat.blockHeader2;
                textCharFmt = docFormat.charHeader2;
                break;

            case 3:
                textBlockFmt = docFormat.blockHeader3;
                textCharFmt = docFormat.charHeader3;
                break;

            case 4:
                textBlockFmt = docFormat.blockHeader4;
                textCharFmt = docFormat.charHeader4;
                break;

            default:
                textBlockFmt = docFormat.blockParagraph;
                textCharFmt = docFormat.charParagraph;
                break;
        }

        textBlockFmt.setAlignment(lineFmt.alignemnt);
        if (lineFmt.indent) {
            textBlockFmt.setTextIndent(docFormat.blockIndent);
        }

        cursor.setBlockFormat(textBlockFmt);

        for (const DocumentBlock::Fragment& blockFrag : newBlock.fragments()) {
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
    }
    cursor.endEditBlock();

    doc->setUndoRedoEnabled(true);

    return;
}

/*
    Encode Document
    ===============
    Encode the content of the QTextDocument block by block onto a list of
    QStrings. This uses a static function in the ColFocBlock class.
*/
QStringList GuiDocEditor::toColletDoc() {
    QStringList docText;
    QTextBlock block = this->document()->firstBlock();
    while(block.isValid()) {
        docText.append(DocumentBlock::encodeQTextBlock(block));
        block = block.next();
    }
    return docText;
}

} // namespace Collett
