/*
Collett – GUI Scene Edit Class
==============================

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

#include "sceneedit.h"

#include <QWidget>
#include <QTextEdit>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QAbstractTextDocumentLayout>

namespace Collett {

GuiSceneEdit::GuiSceneEdit(QWidget *parent)
    : QWidget(parent)
{
    m_editor = new QTextEdit(this);
    m_header = new QWidget(this);
    m_title  = new QLineEdit(this);

    m_editor->setAcceptRichText(true);
    m_editor->setText("Hello World!");

    QVBoxLayout *hLayout = new QVBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(m_title);

    m_header->setLayout(hLayout);

    // Signals and Slots
    connect(
        m_editor->document()->documentLayout(), SIGNAL(documentSizeChanged(const QSizeF&)),
        this, SLOT(newDocumentSize(const QSizeF&))
    );

    // Assemble
    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_header);
    m_layout->addWidget(m_editor);

    this->setLayout(m_layout);
}

void GuiSceneEdit::newDocumentSize(const QSizeF &size) {
    // qInfo() << "Size:" << size;
    m_editor->setMinimumHeight(int(size.height()) + 2*m_editor->frameWidth());
}

} // namespace Collett
