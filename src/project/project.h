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
#include <QDomNode>
#include <QLatin1String>
#include <QList>
#include <QObject>
#include <QString>
#include <QXmlStreamWriter>

namespace Collett {

class ColProject : public QObject
{
    Q_OBJECT

public:
    ColProject(const QString &path);
    ~ColProject();

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
    QList<ColItem*> m_projectTree;

    void setError(const QString &error);

    // XML
    // ===

    // Namespaces
    // Dublin Core: https://dublincore.org/specifications/dublin-core/dcmi-terms/

    QString m_nsCol = QLatin1String("urn:collett:collett");
    QString m_nsPrj = QLatin1String("urn:collett:project");
    QString m_nsMta = QLatin1String("urn:collett:meta");
    QString m_nsItm = QLatin1String("urn:collett:item");
    QString m_nsDC  = QLatin1String("http://purl.org/dc/elements/1.1/");

    // XML Readers
    void readProjectXML(QDomNode &parent);

    // XML Writers
    void writeMetatXML(QXmlStreamWriter &xmlWriter);
    void writeProjectXML(QXmlStreamWriter &xmlWriter);
    void writeContentXML(QXmlStreamWriter &xmlWriter);

};
} // namespace Collett

#endif // COLPROJECT_H
