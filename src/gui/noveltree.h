/*
Collett – GUI Novel Tree Class
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

#ifndef GUINOVELTREE_H
#define GUINOVELTREE_H

#include <QObject>
#include <QTreeWidget>

namespace Collett {

class GuiNovelTree : public QTreeWidget
{
    Q_OBJECT

public:
    GuiNovelTree(QWidget *parent=nullptr);
    ~GuiNovelTree() {};

private:

};
} // namespace Collett

#endif // GUINOVELTREE_H
