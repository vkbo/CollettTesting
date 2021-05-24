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
#include <QDateTime>
#include <QIODevice>
#include <QStringConverter>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

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
    m_hasProject = false;

    // Open XML File

    QFile inFile(m_projectFile.path());
    bool status = inFile.open(QIODevice::ReadOnly);
    if (!status) {
        setError(tr("Could not read project file: %1").arg(m_projectFile.path()));
        return false;
    }

    QXmlStreamReader xmlReader(&inFile);
    xmlReader.setNamespaceProcessing(true);

    if (xmlReader.readNextStartElement()) {
        if (xmlReader.name() == QLatin1String("collettXml") && xmlReader.namespaceUri() == m_nsCol) {
            qInfo() << "collettXml";
        } else {
            setError(tr("Not a valid Collett XML file: %1").arg(m_projectFile.path()));
            inFile.close();
            return false;
        }
    }

    while (xmlReader.readNextStartElement()) {
        qInfo() << "Element:" << xmlReader.name();
        if (xmlReader.name() == QLatin1String("project") && xmlReader.namespaceUri() == m_nsCol) {
            readProjectXML(xmlReader);
        }
    }

    inFile.close();

    m_hasProject = true;

    return true;
}

bool ColProject::saveProject() {

    clearError();

    if (m_projectCreated == "") {
        m_projectCreated = QDateTime::currentDateTime().toString("dd.MM.yyyyThh:mm:ss");
    }

    // Open XML File

    QFile outFile(m_projectFile.path());
    bool status = outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    if (!status) {
        setError(tr("Could not write project file: %1").arg(m_projectFile.path()));
        return false;
    }

    QXmlStreamWriter xmlWriter(&outFile);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(2);
    xmlWriter.writeStartDocument();
    xmlWriter.writeNamespace(m_nsCol, "col");
    xmlWriter.writeNamespace(m_nsMta, "meta");
    xmlWriter.writeNamespace(m_nsItm, "item");
    xmlWriter.writeNamespace(m_nsDC, "dc");
    xmlWriter.writeStartElement(m_nsCol, "collettXml");

    // Write Data

    writeProjectXML(xmlWriter);

    // Close XML File

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    outFile.close();

    return true;
}

/*
    XML Readers
    ===========
*/

void ColProject::readProjectXML(QXmlStreamReader &xmlReader) {

    while (xmlReader.readNextStartElement()) {
        if (xmlReader.name() == QLatin1String("title") && xmlReader.namespaceUri() == m_nsDC) {
            m_projectTitle = xmlReader.readElementText();
        } else if (xmlReader.name() == QLatin1String("created") && xmlReader.namespaceUri() == m_nsDC) {
            m_projectCreated = xmlReader.readElementText();
        } else {
            xmlReader.skipCurrentElement();
        }
    }
}

/*
    XML Writers
    ===========
*/

void ColProject::writeProjectXML(QXmlStreamWriter &xmlWriter) {

    xmlWriter.writeStartElement(m_nsCol, "project");

    xmlWriter.writeStartElement(m_nsDC, "title");
    xmlWriter.writeCharacters(m_projectTitle);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(m_nsDC, "created");
    xmlWriter.writeCharacters(m_projectCreated);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(m_nsDC, "date");
    xmlWriter.writeCharacters(QDateTime::currentDateTime().toString("dd.MM.yyyyThh:mm:ss"));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();

}

} // namespace Collett
