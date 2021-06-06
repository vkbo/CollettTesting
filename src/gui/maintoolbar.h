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

#ifndef GUIMAINTOOLBAR_H
#define GUIMAINTOOLBAR_H

#include "collett.h"

#include <QObject>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QToolButton>

namespace Collett {

class GuiMainToolBar : public QToolBar
{
    Q_OBJECT

public:
    GuiMainToolBar(QWidget *parent=nullptr);
    ~GuiMainToolBar();

public slots:
    void doChangeBlockFormat(int level);
    void fmtBoldClicked();
    void fmtItalicClicked();
    void fmtUnderlineClicked();
    void fmtStrikeoutClicked();
    void alignLeftClicked();
    void alignCentreClicked();
    void alignRightClicked();
    void alignJustifyClicked();
    void textIndentClicked();
    void textOutdentClicked();

signals:
    void documentAction(Collett::DocAction action);

private:

    // Project Menu
    QToolButton *m_projectButton;
    QMenu       *m_projectMenu;
    QAction     *m_projectSave;

    // Document Menu
    QToolButton *m_documentButton;
    QMenu       *m_documentMenu;
    QAction     *m_documentOpen;
    QAction     *m_documentSave;
    QAction     *m_documentNewTitle;
    QAction     *m_documentNewPartition;
    QAction     *m_documentNewChapter;
    QAction     *m_documentNewSection;
    QAction     *m_documentNewScene;
    QAction     *m_documentNewPage;

    // Block Format
    QToolButton *m_blockFormatButton;
    QMenu       *m_blockFormatMenu;
    QAction     *m_blockParagraph;
    QAction     *m_blockHeader1;
    QAction     *m_blockHeader2;
    QAction     *m_blockHeader3;
    QAction     *m_blockHeader4;

    // Text Format
    QAction *m_fmtBold;
    QAction *m_fmtItalic;
    QAction *m_fmtUnderline;
    QAction *m_fmtStrike;

    // Text Alignment
    QAction *m_alignLeft;
    QAction *m_alignCentre;
    QAction *m_alignRight;
    QAction *m_alignJustified;

    // Indent
    QAction *m_textIndent;
    QAction *m_textOutdent;

    void buildProjectMenu();
    void buildDocumentMenu();
    void buildBlockFormatButtons();
    void buildTextFormatButtons();

};
} // namespace Collett

#endif // GUIMAINTOOLBAR_H
