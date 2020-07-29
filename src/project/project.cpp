#include "project.h"

#include <QDebug>
#include <QFile>
#include <QHash>
#include <QXmlStreamReader>

CltProject::CltProject()
{
}

CltProject::~CltProject()
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
int CltProject::openProject(QString fileName, bool overrideLock)
{
    fileName.append("/nwProject.nwx");
    printf("Opening project: %s\n", fileName.toStdString().c_str());

    QFile projFile(fileName);
    if(!projFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Cannot read file" << projFile.errorString();
        return 1;
    }
    QXmlStreamReader nwXML(&projFile);

    return 0;
}
