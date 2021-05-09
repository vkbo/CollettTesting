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

#ifndef COLDOCUMENT_H
#define COLDOCUMENT_H

#include "project.h"

#include <QString>
#include <QStringList>
#include <QFile>

namespace Collett {

class ColDocument
{
public:

    enum RWStatus {
        OK, New, Fail
    };

    ColDocument(ColProject *_project, const QString _handle);
    ~ColDocument();

    void readMeta();

    RWStatus    write(const QString text);
    QStringList paragraphs();
    QString     text();

    bool isValid() {
        return docVaild;
    }

    bool isEmpty() {
        return docEmpty;
    }

    bool exists() {
        return docFile->exists();
    }

private:
    ColProject *project;
    const QString handle;

    QStringList rawMeta;

    bool docVaild;
    bool docEmpty;

    QFile  *docFile;
    QString fileName;
    QString filePath;

};
} // namespace Collett

#endif // COLDOCUMENT_H
