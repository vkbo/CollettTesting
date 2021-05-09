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

#include "constants.h"
#include "project.h"

#include <QDebug>
#include <QFile>
#include <QDir>

namespace Collett {

CollettProject::CollettProject(const QDir path) {

    projectPath = path.absolutePath();
    projectFile = projectPath.absoluteFilePath(COL_PROJECT_FILE_NAME);
    contentPath = QDir(projectPath.path() + "/content");

    if (!contentPath.exists()) {
        if (projectPath.mkdir("content")) {
            qDebug() << "Created folder:" << contentPath.path();
        } else {
            qCritical() << "Could not create folder:" << contentPath.path();
        }
    }

    qDebug() << "Project Path:" << projectPath.path();
    qDebug() << "Project File:" << projectFile.path();
    qDebug() << "Content Path:" << contentPath.path();

}

CollettProject::~CollettProject() {}

bool CollettProject::openProject(bool overrideLock) {

    return true;
}

} // namespace Collett
