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

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QByteArray>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QStringConverter>

namespace Collett {

ColProject::ColProject(const QDir path) {

    m_hasProject = false;
    clearError();

    m_projectPath = path.absolutePath();
    m_projectFile = m_projectPath.absoluteFilePath(COL_PROJECT_FILE_NAME);
    m_contentPath = QDir(m_projectPath.path() + "/content");

    if (!m_contentPath.exists()) {
        if (m_contentPath.mkdir("content")) {
            qDebug() << "Created folder:" << m_contentPath.path();
        } else {
            setError(tr("Could not create folder: %1").arg(m_contentPath.path()));
        }
    }

    qDebug() << "Project Path:" << m_projectPath.path();
    qDebug() << "Project File:" << m_projectFile.path();
    qDebug() << "Content Path:" << m_contentPath.path();

}

ColProject::~ColProject() {}

/*
    Error Handling
*/

void ColProject::clearError() {
    m_hasError = false;
    m_lastError = "";
}

void ColProject::setError(const QString &error) {
    m_hasError = true;
    m_lastError = error;
    qCritical() << error;
}

/*
    Project File I/O
*/

bool ColProject::openProject() {

    clearError();

    // Read JSON File
    // ==============

    QJsonDocument jsonData;
    QFile inFile(m_projectFile.path());
    if (inFile.open(QIODevice::ReadOnly)) {
        QByteArray fileData = inFile.readAll();
        inFile.close();

        QJsonParseError jsonError;
        jsonData = QJsonDocument::fromJson(fileData, &jsonError);
        if (jsonError.error != QJsonParseError::NoError) {
            setError(tr("Could not parse project file: %1").arg(jsonError.errorString()));
            return false;
        }
    } else {
        setError(tr("Could not read project file: %1").arg(m_projectFile.path()));
        return false;
    }

    if (jsonData.isNull()) {
        qCritical() << "Document is empty";
    }

    if (!jsonData.isObject()) {
        setError(tr("Unknown content of project file: %1").arg(m_projectFile.path()));
        return false;
    }

    m_hasProject = true;

    // Extract Content
    // ===============

    QJsonObject jsonObj = jsonData.object();

    if (jsonObj.contains("projectName")) {
        auto value = jsonObj.take("projectName");
        if (value.isString()) {
            m_projectName = value.toString();
            qInfo() << "Project name is:" << m_projectName;
        }
    }

    return true;
}

bool ColProject::saveProject() {

    clearError();

    // Set Values
    // ==========

    QJsonObject jsonObj;

    jsonObj.insert("projectName", m_projectName);

    // Save JSON File
    // ==============

    QJsonDocument jsonData;
    jsonData.setObject(jsonObj);
    QByteArray fileData = jsonData.toJson(QJsonDocument::Indented);
    QFile outFile(m_projectFile.path());
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream ioStream(&outFile);
        ioStream.setEncoding(QStringConverter::Utf8);
        ioStream << fileData;
        outFile.close();
    } else {
        setError(tr("Could not write project file: %1").arg(m_projectFile.path()));
        return false;
    }

    return true;
}

} // namespace Collett
