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

#ifndef GUIFRAGMENTEDIT_H
#define GUIFRAGMENTEDIT_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>

namespace Collett {

class GuiFragmentEdit : public QWidget
{
    Q_OBJECT

public:
    GuiFragmentEdit(QWidget *parent=nullptr);
    ~GuiFragmentEdit() {};

private:
    QVBoxLayout *m_layout;
    QTextEdit   *m_editor;
    QWidget     *m_header;

    QLineEdit *m_title;

private slots:
    void newDocumentSize(const QSizeF &size);

};
} // namespace Collett

#endif // GUIFRAGMENTEDIT_H
