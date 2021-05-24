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

#include <QDir>
#include <QList>
#include <QObject>
#include <QString>
#include <QJsonObject>

namespace Collett {

class ColProject : public QObject
{
    Q_OBJECT

public:
    ColProject(const QDir path);
    ~ColProject();

    // Class Methods
    void clearError();
    bool openProject();
    bool saveProject();

    // Getters
    QDir getProjectPath() {
        return m_projectPath;
    }
    QDir getContentPath() {
        return m_contentPath;
    }
    bool hasProject() {
        return m_hasProject;
    }
    bool hasError() {
        return m_hasError;
    }
    QString lastError() {
        return m_lastError;
    }

private:
    bool    m_hasProject;
    bool    m_hasError;
    QString m_lastError;

    QDir m_projectFile;
    QDir m_projectPath;
    QDir m_contentPath;

    // Project Values
    QString m_projectTitle = "Unnamed Project";
    QString m_projectCreated = "";
    QString m_projectDate = "";

    void setError(const QString &error);

    void readProjectValues(QJsonObject &jsonObj);

    QJsonObject writeProjectValues();
    QJsonObject writeProjectContent();

};
} // namespace Collett

#endif // COLPROJECT_H
