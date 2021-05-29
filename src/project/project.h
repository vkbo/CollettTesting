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

#ifndef COL_PROJECT_H
#define COL_PROJECT_H

#include "collett.h"
#include "storyitem.h"
#include "storytree.h"

#include <QDir>
#include <QDomNode>
#include <QLatin1String>
#include <QList>
#include <QObject>
#include <QString>
#include <QXmlStreamWriter>

namespace Collett {

class Project : public QObject
{
    Q_OBJECT

public:
    Project(const QString &path);
    ~Project();

    // Class Methods
    void clearError();
    bool openProject();
    bool saveProject();

    // Getters
    QDir projectPath() const {
        return m_projectPath;
    }
    QDir contentPath() const {
        return m_contentPath;
    }
    bool hasProject() const {
        return m_hasProject;
    }
    bool hasError() const {
        return m_hasError;
    }
    QString lastError() const {
        return m_lastError;
    }
    StoryTree *storyTree() {
        return m_storyTree;
    }

private:
    bool    m_hasProject;
    bool    m_hasError;
    QString m_lastError;

    QDir m_projectPath;
    QDir m_projectFile;
    QDir m_contentPath;
    bool m_pathValid;

    // Meta Values
    QString m_projectCreated = "";
    int     m_projectRevisions = 0;

    // Project Values
    QString m_projectTitle = "Unnamed Project";
    QString m_projectAuthor = "";

    // Content
    StoryTree *m_storyTree;

    void setError(const QString &error);

    // XML
    // ===

    // Namespaces
    // Dublin Core: https://dublincore.org/specifications/dublin-core/dcmi-terms/

    QString m_nsCol = "urn:collett:collett";
    QString m_nsPrj = "urn:collett:project";
    QString m_nsMta = "urn:collett:meta";
    QString m_nsItm = "urn:collett:item";
    QString m_nsDC  = "http://purl.org/dc/elements/1.1/";

    // XML Readers
    void readProjectXML(QDomNode &parent);

    // XML Writers
    void writeMetatXML(QXmlStreamWriter &xmlWriter);
    void writeProjectXML(QXmlStreamWriter &xmlWriter);
    void writeContentXML(QXmlStreamWriter &xmlWriter);

};
} // namespace Collett

#endif // COL_PROJECT_H
