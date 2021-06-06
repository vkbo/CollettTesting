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
#include "textutils.h"
#include "storyitem.h"

#include <QDebug>
#include <QFont>
#include <QString>
#include <QStringList>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextEdit>

namespace Collett {

GuiDocEditor::GuiDocEditor(QWidget *parent)
    : QTextEdit(parent)
{
    m_data = CollettData::instance();
    m_hasDocument = false;

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
    m_format.blockIndent = 2.0*defaultFontSize;

    // Default
    m_format.blockDefault = defaultBlockFmt;
    m_format.charDefault = defaultCharFmt;

    // Paragraph
    m_format.blockParagraph = defaultBlockFmt;
    m_format.charParagraph = defaultCharFmt;

    // Header 1
    m_format.blockHeader1 = defaultBlockFmt;
    m_format.blockHeader1.setHeadingLevel(1);
    m_format.blockHeader1.setTopMargin(header1FontSize);
    m_format.blockHeader1.setBottomMargin(headerBottomMargin);

    m_format.charHeader1 = defaultCharFmt;
    m_format.charHeader1.setFontPointSize(header1FontSize);

    // Header 2
    m_format.blockHeader2 = defaultBlockFmt;
    m_format.blockHeader2.setHeadingLevel(2);
    m_format.blockHeader2.setTopMargin(header2FontSize);
    m_format.blockHeader2.setBottomMargin(headerBottomMargin);

    m_format.charHeader2 = defaultCharFmt;
    m_format.charHeader2.setFontPointSize(header2FontSize);

    // Header 3
    m_format.blockHeader3 = defaultBlockFmt;
    m_format.blockHeader3.setHeadingLevel(3);
    m_format.blockHeader3.setTopMargin(header3FontSize);
    m_format.blockHeader3.setBottomMargin(headerBottomMargin);

    m_format.charHeader3 = defaultCharFmt;
    m_format.charHeader3.setFontPointSize(header3FontSize);

    // Header 4
    m_format.blockHeader4 = defaultBlockFmt;
    m_format.blockHeader4.setHeadingLevel(4);
    m_format.blockHeader4.setTopMargin(header4FontSize);
    m_format.blockHeader4.setBottomMargin(headerBottomMargin);

    m_format.charHeader4 = defaultCharFmt;
    m_format.charHeader4.setFontPointSize(header4FontSize);

    return;
}

GuiDocEditor::~GuiDocEditor() {
    // delete m_document;
    m_hasDocument = false;
}

/*
    Getters
    =======
*/

bool GuiDocEditor::hasDocument() const {
    return m_hasDocument;
}

bool GuiDocEditor::hasBeenModified() const {
    if (!m_hasDocument) {
        return false;
    }
    return document()->isModified();
}

/*
    Document Functions
    ==================
*/

bool GuiDocEditor::openDocument(const QString &handle) {

    m_hasDocument = false;
    m_document = new Document(m_data->project(), handle);
    m_document->read();

    if (m_document->isValid()) {
        m_hasDocument = true;
        setColletDoc(m_document->paragraphs());
        document()->setModified(false);
    }

    return m_hasDocument;
}

bool GuiDocEditor::saveDocument() {

    StoryItem *item = m_document->item();
    if (item->isEmpty()) {
        return false;
    }

    item->setWordCount(TextUtils::countWords(toPlainText()));
    item->setCursorPosition(textCursor().position());

    QStringList docText = this->toColletDoc();
    for (int i=0; i < docText.size(); ++i) {
        qInfo() << docText.at(i);
    }
    if (m_hasDocument) {
        m_document->write(docText.join("\n"));
        document()->setModified(false);
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
        DocumentBlock::Block newBlock = DocumentBlock::decodeText(line);
        if (!newBlock.valid) {
            qWarning() << "Invalid block encountered";
            continue;
        }

        if (isFirst) {
            isFirst = false;
        } else {
            cursor.insertBlock();
        }

        QTextBlockFormat textBlockFmt = m_format.blockDefault;
        QTextCharFormat textCharFmt = m_format.charDefault;

        DocumentBlock::Styles lineFmt = newBlock.styles;
        switch (lineFmt.header) {
            case 1:
                textBlockFmt = m_format.blockHeader1;
                textCharFmt = m_format.charHeader1;
                break;

            case 2:
                textBlockFmt = m_format.blockHeader2;
                textCharFmt = m_format.charHeader2;
                break;

            case 3:
                textBlockFmt = m_format.blockHeader3;
                textCharFmt = m_format.charHeader3;
                break;

            case 4:
                textBlockFmt = m_format.blockHeader4;
                textCharFmt = m_format.charHeader4;
                break;

            default:
                textBlockFmt = m_format.blockParagraph;
                textCharFmt = m_format.charParagraph;
                break;
        }

        textBlockFmt.setAlignment(lineFmt.alignemnt);
        if (lineFmt.indent) {
            textBlockFmt.setTextIndent(m_format.blockIndent);
        }

        cursor.setBlockFormat(textBlockFmt);

        for (const DocumentBlock::Fragment& blockFrag : newBlock.fragments) {
            if (blockFrag.plain) {
                cursor.insertText(blockFrag.text, textCharFmt);
            } else {
                QTextCharFormat textFragFmt = textCharFmt;
                textFragFmt.setFontWeight(blockFrag.bold ? QFont::Bold : QFont::Normal);
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
