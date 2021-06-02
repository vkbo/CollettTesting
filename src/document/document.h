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

#ifndef COL_DOCUMENT_H
#define COL_DOCUMENT_H

#include "project.h"

#include <QString>
#include <QStringList>
#include <QFile>
#include <QObject>

namespace Collett {

class Document : public QObject
{
    Q_OBJECT

public:
    enum DocumentType {
        Story, Note
    };

    enum RWStatus {
        OK, New, Fail
    };

    Document(Project *_project, const QString _handle);
    ~Document();

    void readMeta();

    RWStatus write(const QString &text);
    RWStatus read();

    bool isValid() const;
    bool isEmpty() const;
    bool exists() const;

    QStringList paragraphs() const;
    QString     toPlainText();

    void clearError();

private:
    Project *project;
    const QString m_handle;

    QStringList m_rawMeta;
    QStringList m_rawText;

    bool    m_valid;
    bool    m_empty;
    bool    m_hasError;
    QString m_errMessage;

    QFile  *m_file;
    QString m_fileName;
    QString m_filePath;

};
} // namespace Collett

#endif // COL_DOCUMENT_H
