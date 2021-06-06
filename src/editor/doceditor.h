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

#ifndef GUIDOCEDITOR_H
#define GUIDOCEDITOR_H

#include "collett.h"
#include "data.h"
#include "project.h"
#include "document.h"

#include <QObject>
#include <QStringList>
#include <QTextEdit>
#include <QString>
#include <QTextBlock>
#include <QTextDocument>
#include <QTextBlockFormat>
#include <QTextCharFormat>

namespace Collett {

class GuiDocEditor : public QTextEdit
{
    Q_OBJECT

public:

    struct DocFormat {
        QTextBlockFormat blockDefault;
        QTextCharFormat  charDefault;
        QTextBlockFormat blockParagraph;
        QTextCharFormat  charParagraph;
        QTextBlockFormat blockHeader1;
        QTextCharFormat  charHeader1;
        QTextBlockFormat blockHeader2;
        QTextCharFormat  charHeader2;
        QTextBlockFormat blockHeader3;
        QTextCharFormat  charHeader3;
        QTextBlockFormat blockHeader4;
        QTextCharFormat  charHeader4;
        qreal blockIndent;
    };

    GuiDocEditor(QWidget *parent=nullptr);
    ~GuiDocEditor();

    bool openDocument(const QString &handle);
    bool saveDocument();

    bool hasDocument() const;
    bool hasBeenModified() const;

public slots:
    void documentAction(Collett::DocAction action);

private:
    CollettData *m_data;
    Document    *m_document;
    DocFormat    m_format;

    bool m_hasDocument;

    void setColletDoc(const QStringList &content);
    QStringList toColletDoc();

};
} // namespace Collett

#endif // GUIDOCEDITOR_H
