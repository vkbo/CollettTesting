/*
Collett – GUI Edit Area Class
=============================

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

#include "editarea.h"
#include "sceneedit.h"

#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>

namespace Collett {

GuiEditArea::GuiEditArea(QWidget *parent)
    : QScrollArea(parent)
{
    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);

    this->setWidget(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    QWidget *editOne = new GuiSceneEdit(this);
    QWidget *editTwo = new GuiSceneEdit(this);

    m_centralLayout->addWidget(editOne);
    m_centralLayout->addWidget(editTwo);
    m_centralLayout->addStretch(1);

    this->setWidgetResizable(true);
}

} // namespace Collett
