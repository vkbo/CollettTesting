#include "project.h"

#include <QDebug>
#include <QFile>
#include <QHash>
#include <QXmlStreamReader>

Project::Project()
{
}

Project::~Project()
{
}

// ============================================================================================== //
//  Class Methods
// ============================================================================================== //

/*
 * Open the project file provided, or if doesn't exist, assume it is a folder, and look for the file
 * within it. If successful, parse the XML of the file and populate the project variables and build
 * the tree of project items.
 */
int Project::openProject(QString fileName, bool overrideLock)
{
    if (!fileName.endsWith("/")) fileName.append("/");
    fileName.append("nwProject.nwx");
    printf("Opening project: %s\n", fileName.toStdString().c_str());

    QFile projFile(fileName);
    if (!projFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Cannot read file" << projFile.errorString();
        return 1;
    }
    QXmlStreamReader prjXML(&projFile);

    while (!prjXML.atEnd()) {
        auto tType = prjXML.readNext();
        switch (tType) {
            case QXmlStreamReader::StartElement:
                qDebug() << tType << prjXML.tokenString() << prjXML.name() << prjXML.text();
                break;
            case QXmlStreamReader::EndElement:
                qDebug() << tType << prjXML.tokenString() << prjXML.name() << prjXML.text();
                break;
            case QXmlStreamReader::Characters:
                qDebug() << tType << prjXML.tokenString() << prjXML.name() << prjXML.text();
                break;
        }
    }

    return 0;
}
