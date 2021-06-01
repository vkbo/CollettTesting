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
#include <QStringList>

#include <QDebug>

namespace Collett {

Document::Document(Project *_project, const QString _handle)
    : project(_project), m_handle(_handle)
{
    QDir contentPath = project->contentPath();
    if (!contentPath.exists()) {
        qWarning() << "Cannot initialise document object as content path does not exist";
        m_valid = false;
        m_empty = true;
        return;
    }

    m_fileName = m_handle+".ctxt";
    m_filePath = contentPath.absoluteFilePath(m_fileName);

    m_file = new QFile(m_filePath);
}

Document::~Document() {}

/*
    Methods
    =======
*/

void Document::readMeta() {

    QString line;

    rawMeta.clear();
    if (m_file->open(QIODevice::ReadOnly)) {
        QTextStream inStream(m_file);
        while (!inStream.atEnd()) {
            line = inStream.readLine();
            if (line.startsWith("[META:")) {
                rawMeta.append(line);
            } else {
                break;
            }
        }
        m_file->close();
    }

    return;
}

QStringList Document::paragraphs() {

    QStringList content;
    QString line;

    if (m_file->open(QIODevice::ReadOnly)) {
        QTextStream inStream(m_file);
        while (!inStream.atEnd()) {
            line = inStream.readLine();
            if (!line.startsWith("[META:")) {
                content.append(line);
            }
        }
        m_file->close();
    }

    return content;
}

QString Document::text() {
    return paragraphs().join('\n');
}

Document::RWStatus Document::write(const QString &text) {

    if (m_file->open(QIODevice::WriteOnly)) {
        QTextStream stream(m_file);
        stream << text << '\n';
        m_file->close();
        qDebug() << "Wrote document:" << m_filePath;
    } else {
        return Document::RWStatus::Fail;
    }

    return Document::RWStatus::OK;
}

} // namespace Collett
