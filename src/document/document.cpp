/*
Collett – Document Class
========================

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

#include "document.h"
#include "project.h"

#include <QDir>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

namespace Collett {

ColDocument::ColDocument(ColProject *_project, const QString _handle)
    : project(_project), handle(_handle)
{
    fileName = handle + ".ctxt";
}

ColDocument::~ColDocument() {}

/*
    Methods
    =======
*/

ColDocument::RWStatus ColDocument::read() {

    return ColDocument::RWStatus::OK;
}

ColDocument::RWStatus ColDocument::write(const QString text) {

    QDir contentPath = project->getContentPath();
    if (!contentPath.exists()) {
        qCritical() << "Folder does not exits:" << contentPath.path();
        return ColDocument::RWStatus::Fail;
    }

    QString outPath = contentPath.absoluteFilePath(fileName);
    QFile file(outPath);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << text << '\n';
        qDebug() << "Wrote document:" << outPath;
    } else {
        return ColDocument::RWStatus::Fail;
    }

    return ColDocument::RWStatus::OK;
}

} // namespace Collett
