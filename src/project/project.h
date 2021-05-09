/*
Collett – Project Class
=======================

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

#ifndef COLPROJECT_H
#define COLPROJECT_H

#include "collett.h"
#include "item.h"

#include <QString>
#include <QDir>

namespace Collett {

class ColProject
{

public:
    ColProject(const QDir path);
    ~ColProject();

    // Class Methods
    bool openProject(bool overrideLock=false);

    // Getters
    QDir getProjectPath() {
        return projectPath;
    }
    QDir getContentPath() {
        return contentPath;
    }

private:
    QDir projectFile;
    QDir projectPath;
    QDir contentPath;

};
} // namespace Collett

#endif // COLPROJECT_H
