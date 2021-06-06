/*
Collett – GUI Main Tool Bar Class
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

#include "collett.h"
#include "maintoolbar.h"

#include <QAction>
#include <QIcon>
#include <QKeySequence>
#include <QMenu>
#include <QObject>
#include <QSize>
#include <QToolBar>
#include <QToolButton>

namespace Collett {

GuiMainToolBar::GuiMainToolBar(QWidget *parent)
    : QToolBar(parent)
{

    setIconSize(QSize(18, 18));
    setToolButtonStyle(Qt::ToolButtonIconOnly);

    buildProjectMenu();
    buildDocumentMenu();
    addSeparator();
    buildBlockFormatButtons();
    addSeparator();
    buildTextFormatButtons();

}

GuiMainToolBar::~GuiMainToolBar() {}

/*
    Slots
    =====
*/

void GuiMainToolBar::doChangeBlockFormat(int level) {

    m_blockParagraph->setChecked(false);
    m_blockHeader1->setChecked(false);
    m_blockHeader2->setChecked(false);
    m_blockHeader3->setChecked(false);
    m_blockHeader4->setChecked(false);

    switch (level) {
        case 0:
            m_blockParagraph->setChecked(true);
            break;
        case 1:
            m_blockHeader1->setChecked(true);
            break;
        case 2:
            m_blockHeader2->setChecked(true);
            break;
        case 3:
            m_blockHeader3->setChecked(true);
            break;
        case 4:
            m_blockHeader4->setChecked(true);
            break;
    }
}

void GuiMainToolBar::fmtBoldClicked() {
    emit documentAction(Collett::FormatBold);
}

void GuiMainToolBar::fmtItalicClicked() {
    emit documentAction(Collett::FormatItalic);
}

void GuiMainToolBar::fmtUnderlineClicked() {
    emit documentAction(Collett::FormatUnderline);
}

void GuiMainToolBar::fmtStrikeoutClicked() {
    emit documentAction(Collett::FormatStrikeOut);
}

void GuiMainToolBar::alignLeftClicked() {
    emit documentAction(Collett::TextAlignLeft);
}

void GuiMainToolBar::alignCentreClicked() {
    emit documentAction(Collett::TextAlignCentre);
}

void GuiMainToolBar::alignRightClicked() {
    emit documentAction(Collett::TextAlignRight);
}

void GuiMainToolBar::alignJustifyClicked() {
    emit documentAction(Collett::TextAlignJustify);
}

void GuiMainToolBar::textIndentClicked() {
    emit documentAction(Collett::TextIndent);
}

void GuiMainToolBar::textOutdentClicked() {
    emit documentAction(Collett::TextOutdent);
}

/*
    Build Button Rows
    =================
*/

/*
    Construct Project menu button.
*/
void GuiMainToolBar::buildProjectMenu() {

    m_projectMenu = new QMenu(this);

    m_projectSave = m_projectMenu->addAction(tr("Save Project"));

    m_projectSave->setIcon(QIcon(":/icons/light/save.svg"));

    // Assemble Menu
    m_projectButton = new QToolButton(this);
    m_projectButton->setIcon(QIcon(":/icons/light/book.svg"));
    m_projectButton->setText("Project");
    m_projectButton->setMenu(m_projectMenu);
    m_projectButton->setPopupMode(QToolButton::InstantPopup);
    addWidget(m_projectButton);
}

/*
    Construct Document menu button.
*/
void GuiMainToolBar::buildDocumentMenu() {

    m_documentMenu = new QMenu(this);

    m_documentOpen = m_documentMenu->addAction(tr("Open Document"));
    m_documentSave = m_documentMenu->addAction(tr("Save Document"));
    m_documentMenu->addSeparator();
    m_documentNewTitle = m_documentMenu->addAction(tr("New Title Page"));
    m_documentNewPartition = m_documentMenu->addAction(tr("New Partition"));
    m_documentNewChapter = m_documentMenu->addAction(tr("New Chapter"));
    m_documentNewSection = m_documentMenu->addAction(tr("New Section"));
    m_documentNewScene = m_documentMenu->addAction(tr("New Scene"));
    m_documentNewPage = m_documentMenu->addAction(tr("New Page"));

    m_documentOpen->setIcon(QIcon(":/icons/light/open.svg"));
    m_documentSave->setIcon(QIcon(":/icons/light/save.svg"));
    m_documentNewTitle->setIcon(QIcon(":/icons/light/document-add.svg"));
    m_documentNewPartition->setIcon(QIcon(":/icons/light/document-add.svg"));
    m_documentNewChapter->setIcon(QIcon(":/icons/light/document-add.svg"));
    m_documentNewSection->setIcon(QIcon(":/icons/light/document-add.svg"));
    m_documentNewScene->setIcon(QIcon(":/icons/light/document-add.svg"));
    m_documentNewPage->setIcon(QIcon(":/icons/light/document-add.svg"));

    m_documentOpen->setShortcut(QKeySequence("Ctrl+O"));
    m_documentSave->setShortcut(QKeySequence("Ctrl+S"));
    m_documentNewTitle->setShortcut(QKeySequence("Ctrl+N, T"));
    m_documentNewPartition->setShortcut(QKeySequence("Ctrl+N, P"));
    m_documentNewChapter->setShortcut(QKeySequence("Ctrl+N, C"));
    m_documentNewSection->setShortcut(QKeySequence("Ctrl+N, X"));
    m_documentNewScene->setShortcut(QKeySequence("Ctrl+N, S"));
    m_documentNewPage->setShortcut(QKeySequence("Ctrl+N, G"));

    // Assemble Menu
    m_documentButton = new QToolButton(this);
    m_documentButton->setIcon(QIcon(":/icons/light/document.svg"));
    m_documentButton->setText("Project");
    m_documentButton->setMenu(m_documentMenu);
    m_documentButton->setPopupMode(QToolButton::InstantPopup);
    addWidget(m_documentButton);
}

/*
    Construct block format buttons.
*/
void GuiMainToolBar::buildBlockFormatButtons() {

    m_blockFormatMenu = new QMenu(this);

    m_blockParagraph = m_blockFormatMenu->addAction(tr("Paragraph"));
    m_blockHeader1 = m_blockFormatMenu->addAction(tr("Header 1"));
    m_blockHeader1 = m_blockFormatMenu->addAction(tr("Header 2"));
    m_blockHeader1 = m_blockFormatMenu->addAction(tr("Header 3"));
    m_blockHeader1 = m_blockFormatMenu->addAction(tr("Header 4"));

    // Assemble Menu
    m_blockFormatButton = new QToolButton(this);
    m_blockFormatButton->setText("Format");
    m_blockFormatButton->setMenu(m_blockFormatMenu);
    m_blockFormatButton->setPopupMode(QToolButton::InstantPopup);
    addWidget(m_blockFormatButton);
}

/*
    Construct text formatting buttons.
*/
void GuiMainToolBar::buildTextFormatButtons() {

    m_fmtBold = addAction(tr("Bold"));
    m_fmtItalic = addAction(tr("Italic"));
    m_fmtUnderline = addAction(tr("Underline"));
    m_fmtStrike = addAction(tr("Strikethrough"));

    m_fmtBold->setIcon(QIcon(":/icons/light/format-bold.svg"));
    m_fmtItalic->setIcon(QIcon(":/icons/light/format-italic.svg"));
    m_fmtUnderline->setIcon(QIcon(":/icons/light/format-underline.svg"));
    m_fmtStrike->setIcon(QIcon(":/icons/light/format-strikeout.svg"));

    m_fmtBold->setShortcut(QKeySequence("Ctrl+B"));
    m_fmtItalic->setShortcut(QKeySequence("Ctrl+I"));
    m_fmtUnderline->setShortcut(QKeySequence("Ctrl+U"));
    m_fmtStrike->setShortcut(QKeySequence("Ctrl+D"));

    connect(m_fmtBold, &QAction::triggered, this, &GuiMainToolBar::fmtBoldClicked);
    connect(m_fmtItalic, &QAction::triggered, this, &GuiMainToolBar::fmtItalicClicked);
    connect(m_fmtUnderline, &QAction::triggered, this, &GuiMainToolBar::fmtUnderlineClicked);
    connect(m_fmtStrike, &QAction::triggered, this, &GuiMainToolBar::fmtStrikeoutClicked);

    addSeparator();

    m_alignLeft = addAction(tr("Left Align"));
    m_alignCentre = addAction(tr("Centre Align"));
    m_alignRight = addAction(tr("Right Align"));
    m_alignJustified = addAction(tr("Justified"));

    m_alignLeft->setIcon(QIcon(":/icons/light/align-left.svg"));
    m_alignCentre->setIcon(QIcon(":/icons/light/align-center.svg"));
    m_alignRight->setIcon(QIcon(":/icons/light/align-right.svg"));
    m_alignJustified->setIcon(QIcon(":/icons/light/align-justify.svg"));

    connect(m_alignLeft, &QAction::triggered, this, &GuiMainToolBar::alignLeftClicked);
    connect(m_alignCentre, &QAction::triggered, this, &GuiMainToolBar::alignCentreClicked);
    connect(m_alignRight, &QAction::triggered, this, &GuiMainToolBar::alignRightClicked);
    connect(m_alignJustified, &QAction::triggered, this, &GuiMainToolBar::alignJustifyClicked);

    addSeparator();

    m_textIndent = addAction(tr("Indent"));
    m_textOutdent = addAction(tr("Outdent"));

    m_textIndent->setIcon(QIcon(":/icons/light/text-indent.svg"));
    m_textOutdent->setIcon(QIcon(":/icons/light/text-outdent.svg"));

    connect(m_textIndent, &QAction::triggered, this, &GuiMainToolBar::textIndentClicked);
    connect(m_textOutdent, &QAction::triggered, this, &GuiMainToolBar::textOutdentClicked);

}

} // namespace Collett
