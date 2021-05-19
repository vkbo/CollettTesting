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

#include <QTextEdit>
#include <QSizePolicy>
#include <QAbstractTextDocumentLayout>

namespace Collett {

GuiSceneEdit::GuiSceneEdit(QWidget *parent)
    : QTextEdit(parent)
{
    this->setAcceptRichText(true);
    this->setText("Hello World!");

    // this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    connect(
        this->document()->documentLayout(), SIGNAL(documentSizeChanged(const QSizeF&)),
        this, SLOT(newDocumentSize(const QSizeF&))
    );
}

void GuiSceneEdit::newDocumentSize(const QSizeF &size) {
    // qInfo() << "Size:" << size;
    this->setMinimumHeight(int(size.height()) + 10);
}

} // namespace Collett
