/*
Collett – Core Data Class
=========================

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

#ifndef COLLETTDATA_H
#define COLLETTDATA_H

#include "collett.h"
#include "project.h"

#include <QWidget>
#include <QString>
#include <QDir>

namespace Collett {

class CollettData
{

public:
    CollettData(QWidget *parent) : m_parent(parent) {};
    ~CollettData() {};

    Project* getProject();

    bool openProject(const QString &path);
    bool saveProject();

private:
    bool m_hasProject = false;

    QWidget    *m_parent;
    Project *m_project;

};
} // namespace Collett

#endif // COLLETTDATA_H
