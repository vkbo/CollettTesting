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
#include "documentblock.h"
#include "textutils.h"
#include "storyitem.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QtGlobal>

namespace Collett {

/*
    Constructor/Destructor
    ======================
*/

Document::Document(Project *project, const QString &handle)
    : m_project(project), m_handle(handle)
{
    clearError();

    if (!TextUtils::isHandle(m_handle)) {
        addError(tr("An error occured while initialising document."));
        qWarning() << QString("Document ERROR: Handle '%1' is not valid").arg(m_handle);
        m_valid = false;
        m_empty = true;
        return;
    }

    QDir contentPath = m_project->contentPath();
    if (!contentPath.exists()) {
        addError(tr("An error occured while initialising document."));
        qWarning() << "Document ERROR: Cannot initialise document object as content path does not exist";
        m_valid = false;
        m_empty = true;
        return;
    }

    m_item = m_project->storyTree()->itemWithHandle(m_handle);
    if (m_item->isEmpty()) {
        addError(tr("The document is not known to the project and cannot be saved."));
        m_valid = false;
        m_empty = true;
        return;
    }

    m_fileName = m_handle+".ctxt";
    m_filePath = contentPath.absoluteFilePath(m_fileName);

    m_file = new QFile(m_filePath);
    m_valid = true;
    m_empty = true;
}

Document::~Document() {
    if (m_file->isOpen()) {
        m_file->close();
    }
    delete m_file;
}

/*
    Getters
    =======
*/

bool Document::isValid() const {
    return m_valid;
}

bool Document::isEmpty() const {
    return m_empty;
}

bool Document::exists() const {
    return m_file->exists();
}

QStringList Document::paragraphs() const {
    if (m_valid && !m_empty) {
        return m_rawText;
    } else {
        return QStringList();
    }
}

StoryItem *Document::item() const {
    return m_item;
}

/*
    Read/Write
    ==========
*/

Document::RWStatus Document::read() {

    m_empty = true;
    m_rawMeta.clear();
    m_rawText.clear();

    if (!m_file->exists()) {
        m_valid = true;
        m_empty = true;
        return RWStatus::New;
    }

    if (m_file->open(QIODevice::ReadOnly)) {
        QString line;
        QTextStream inStream(m_file);
        while (!inStream.atEnd()) {
            line = inStream.readLine();
            if (line.startsWith("[META:")) {
                m_rawMeta.append(line);
            } else if (line.startsWith("[")) {
                m_rawText.append(line);
            }
        }
        m_file->close();

        m_valid = true;
        m_empty = false;
        return RWStatus::OK;
    } else {
        m_valid = false;
        m_empty = true;
        return RWStatus::Fail;
    }
}

Document::RWStatus Document::write(const QString &text) {

    if (!checkBeforeIO()) {
        return RWStatus::Fail;
    }

    if (m_file->open(QIODevice::WriteOnly)) {
        QTextStream stream(m_file);

        // Meta Data
        stream << "[META:TITLE]" << m_item->title() << "\n";
        stream << "[META:WORDS]" << m_item->wordCount() << "\n";

        // Body Text
        stream << text << '\n';

        // Close and Report
        m_file->close();
        qDebug() << "Wrote document:" << m_filePath;

    } else {
        return Document::RWStatus::Fail;
    }

    return RWStatus::OK;
}

/*
    Parsing
    =======
*/

QString Document::toPlainText() {

    QString text;
    int errCount = 0;

    for (const QString& line : m_rawText) {
        DocumentBlock::Block block = DocumentBlock::decodeText(line);
        if (!block.valid) {
            errCount++;
            continue;
        }
        text.append(block.text).append('\n');
    }

    clearError();
    if (errCount > 0) {
        addError(
            tr("Encountered %1 error(s) while parsing document file: %2")
            .arg(errCount)
            .arg(m_file->fileName())
        );
    }

    return text;
}

/*
    Other Methods
    =============
*/

void Document::clearError() {
    m_hasError = false;
    m_errMessages.clear();
}

/*
    Internal Functions
    ==================
*/

void Document::addError(const QString &err) {
    m_hasError = true;
    m_errMessages.append(err);
    qWarning() << "Document ERROR:" << err;
}

bool Document::checkBeforeIO() {
    if (m_valid) {
        return true;
    } else {
        addError(tr("Cannot perform action on invalid document."));
        return false;
    }
}

} // namespace Collett
