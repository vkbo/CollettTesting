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

CollettProject::CollettProject(const QDir path) {

    projectPath = path.absolutePath();
    projectFile = projectPath.absoluteFilePath(COL_PROJECT_FILE_NAME);

    qDebug() << "Project Path:" << projectPath.path();
    qDebug() << "Project File:" << projectFile.path();

}

CollettProject::~CollettProject() {}

/*
 * Open the project file provided, or if doesn't exist, assume it is a folder, and look for the file
 * within it. If successful, parse the XML of the file and populate the project variables and build
 * the tree of project items.
 */
int CollettProject::openProject(QString fileName, bool overrideLock) {

    if (!fileName.endsWith("/")) fileName.append("/");
    fileName.append("project.collett");
    qInfo() << "Opening project:" << fileName;

    QFile projFile(fileName);
    if (!projFile.open(QFile::ReadOnly | QFile::Text)){
        qCritical() << "Cannot read file" << projFile.errorString();
        return 1;
    }

    return 0;
}
