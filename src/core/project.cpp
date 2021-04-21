#include "project.h"

#include <QDebug>
#include <QFile>

Project::Project() {}

Project::~Project() {}

// ============================================================================================== //
//  Class Methods
// ============================================================================================== //

/*
 * Open the project file provided, or if doesn't exist, assume it is a folder, and look for the file
 * within it. If successful, parse the XML of the file and populate the project variables and build
 * the tree of project items.
 */
int Project::openProject(QString fileName, bool overrideLock) {

    if (!fileName.endsWith("/")) fileName.append("/");
    fileName.append("nwProject.nwx");
    qInfo() << "Opening project:" << fileName;

    QFile projFile(fileName);
    if (!projFile.open(QFile::ReadOnly | QFile::Text)){
        qCritical() << "Cannot read file" << projFile.errorString();
        return 1;
    }

    return 0;
}
