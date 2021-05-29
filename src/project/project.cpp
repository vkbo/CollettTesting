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
#include "storytree.h"

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QXmlStreamWriter>

namespace Collett {

Project::Project(const QString &path) {

    clearError();
    m_hasProject = false;
    m_pathValid = false;
    m_storyTree = new StoryTree(this);

    // If the path is a file, go one level up
    QFileInfo fObj = QFileInfo(path);
    if (!fObj.exists()) {
        setError(tr("Project not found at: %1").arg(path));
        return;
    }

    QDir projDir = QDir(path).absolutePath();
    if (fObj.isFile()) {
        projDir = fObj.dir().absolutePath();
    }

    // Check that the folder exists
    QDir projFile = projDir.filePath(COL_PROJECT_FILE_NAME);
    if (!QFileInfo::exists(projFile.path())) {
        setError(tr("Project not found at: %1").arg(projFile.path()));
        return;
    }

    // Set the path variables
    m_projectPath = projDir;
    m_projectFile = projFile;
    m_contentPath = QDir(m_projectPath.path() + "/content");

    // Verify that the needed project folders exist
    if (!m_contentPath.exists()) {
        if (m_contentPath.mkdir("content")) {
            qDebug() << "Created folder:" << m_contentPath.path();
        } else {
            setError(tr("Could not create folder: %1").arg(m_contentPath.path()));
            return;
        }
    }

    m_pathValid = true;

    qDebug() << "Project Path:" << m_projectPath.path();
    qDebug() << "Project File:" << m_projectFile.path();
    qDebug() << "Content Path:" << m_contentPath.path();

    m_storyTree->createItem(StoryItem::Title, "Title Page");
    m_storyTree->createItem(StoryItem::Chapter, "Chapter One");
    m_storyTree->createItem(StoryItem::Scene, "Scene One");
    m_storyTree->createItem(StoryItem::Scene, "Scene Two");
    m_storyTree->createItem(StoryItem::Chapter, "Chapter Two");
    m_storyTree->createItem(StoryItem::Scene, "Scene Three");
    m_storyTree->createItem(StoryItem::Scene, "Scene Four");

}

Project::~Project() {
    delete m_storyTree;
}

/*
    Error Handling
*/

void Project::clearError() {
    m_hasError = false;
    m_lastError = "";
}

void Project::setError(const QString &error) {
    m_hasError = true;
    m_lastError = error;
    qCritical() << error;
}

/*
    Project File I/O
*/

bool Project::openProject() {

    if (!m_pathValid) return false;
    clearError();

    // Open XML File

    QDomDocument doc;
    QFile inFile(m_projectFile.path());
    if (!inFile.open(QIODevice::ReadOnly)) {
        setError(tr("Could not read project file: %1").arg(m_projectFile.path()));
        return false;
    }

    // Parse XML

    QString errString = "";
    int errLine = -1, errCol = -1;
    if (!doc.setContent(&inFile, true, &errString, &errLine, &errCol)) {
        setError(tr("Could not parse project file XML content. Error on line %1, column %2: %3").arg(
            QString().setNum(errLine), QString().setNum(errCol), errString
        ));
        inFile.close();
        return false;
    }
    inFile.close();

    // Read Content
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    while(!node.isNull()) {
        QDomElement element = node.toElement();
        if(!element.isNull()) {
            if (element.namespaceURI() == m_nsCol) {
                if (element.tagName() == "project") {
                    readProjectXML(node);
                }
            }
            qInfo() << element.namespaceURI() << element.tagName();
        }
        node = node.nextSibling();
    }

    m_hasProject = true;

    return true;
}

bool Project::saveProject() {

    if (!m_pathValid) return false;
    clearError();

    if (m_projectCreated == "") {
        m_projectCreated = QDateTime::currentDateTime().toString(Qt::ISODate);
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
    xmlWriter.writeNamespace(m_nsCol, "collett");
    xmlWriter.writeNamespace(m_nsPrj, "project");
    xmlWriter.writeNamespace(m_nsMta, "meta");
    xmlWriter.writeNamespace(m_nsItm, "item");
    xmlWriter.writeNamespace(m_nsDC, "dc");
    xmlWriter.writeStartElement(m_nsCol, "collettXml");

    // Write Data

    writeMetatXML(xmlWriter);
    writeProjectXML(xmlWriter);
    writeContentXML(xmlWriter);

    // Close XML File

    xmlWriter.writeEndElement(); // Close: collettXml
    xmlWriter.writeEndDocument(); // Close: Document
    outFile.close();

    return true;
}

/*
    XML Readers
    ===========
*/

void Project::readProjectXML(QDomNode &parent) {

    QDomNode node = parent.firstChild();
    while(!node.isNull()) {
        QDomElement element = node.toElement();
        if(!element.isNull()) {

            // Dublin Core
            if (element.namespaceURI() == m_nsDC) {
                if (element.tagName() == QLatin1String("title")) {
                    m_projectTitle = element.text();
                } else if (element.tagName() == QLatin1String("created")) {
                    m_projectCreated = element.text();
                }
            }
            qInfo() << element.namespaceURI() << element.tagName();
        }
        node = node.nextSibling();
    }
}

/*
    XML Writers
    ===========
*/

void Project::writeMetatXML(QXmlStreamWriter &xmlWriter) {

    xmlWriter.writeStartElement(m_nsCol, "meta");

    xmlWriter.writeStartElement(m_nsDC, "created");
    xmlWriter.writeCharacters(m_projectCreated);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(m_nsDC, "date");
    xmlWriter.writeCharacters(QDateTime::currentDateTime().toString(Qt::ISODate));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(m_nsMta, "revisions");
    xmlWriter.writeCharacters(QString().setNum(m_projectRevisions));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement(); // Close: meta

    return;
}

void Project::writeProjectXML(QXmlStreamWriter &xmlWriter) {

    xmlWriter.writeStartElement(m_nsCol, "project");

    xmlWriter.writeStartElement(m_nsDC, "title");
    xmlWriter.writeCharacters(m_projectTitle);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(m_nsPrj, "author");
    xmlWriter.writeCharacters(m_projectAuthor);
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement(); // Close: project

    return;
}

void Project::writeContentXML(QXmlStreamWriter &xmlWriter) {

    xmlWriter.writeStartElement(m_nsCol, "content");
    m_storyTree->toXML(m_nsCol, m_nsItm, xmlWriter);
    xmlWriter.writeEndElement(); // Close: content

    return;
}

} // namespace Collett
