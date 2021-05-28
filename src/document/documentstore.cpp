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

#include "documentstore.h"
#include "project.h"

#include <QDir>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QStringList>

#include <QDebug>

namespace Collett {

DocumentStore::DocumentStore(Project *_project, const QString _handle)
    : project(_project), handle(_handle)
{
    QDir contentPath = project->contentPath();
    if (!contentPath.exists()) {
        qWarning() << "Cannot initialise document object as content path does not exist";
        docVaild = false;
        docEmpty = true;
        return;
    }

    fileName = handle+".ctxt";
    filePath = contentPath.absoluteFilePath(fileName);

    docFile = new QFile(filePath);
}

DocumentStore::~DocumentStore() {}

/*
    Methods
    =======
*/

void DocumentStore::readMeta() {

    QString line;

    rawMeta.clear();
    if (docFile->open(QIODevice::ReadOnly)) {
        QTextStream inStream(docFile);
        while (!inStream.atEnd()) {
            line = inStream.readLine();
            if (line.startsWith("[META:")) {
                rawMeta.append(line);
            } else {
                break;
            }
        }
        docFile->close();
    }

    return;
}

QStringList DocumentStore::paragraphs() {

    QStringList content;
    QString line;

    if (docFile->open(QIODevice::ReadOnly)) {
        QTextStream inStream(docFile);
        while (!inStream.atEnd()) {
            line = inStream.readLine();
            if (!line.startsWith("[META:")) {
                content.append(line);
            }
        }
        docFile->close();
    }

    return content;
}

QString DocumentStore::text() {
    return paragraphs().join('\n');
}

DocumentStore::RWStatus DocumentStore::write(const QString text) {

    if (docFile->open(QIODevice::WriteOnly)) {
        QTextStream stream(docFile);
        stream << text << '\n';
        docFile->close();
        qDebug() << "Wrote document:" << filePath;
    } else {
        return DocumentStore::RWStatus::Fail;
    }

    return DocumentStore::RWStatus::OK;
}

} // namespace Collett
