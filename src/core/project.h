#ifndef PROJECT_H
#define PROJECT_H

#include "collett.h"
#include "item.h"

#include <QString>
#include <QList>
#include <QHash>

class Project
{

public:
    Project();
    ~Project();

    // Class Methods
    int openProject(QString fileName, bool overrideLock=false);

private:
    qint64         projOpened  = 0;     // The time stamp of when the project file was opened
    bool           projChanged = false; // The project has unsaved changes
    bool           projAltered = false; // The project has been altered this session
    QList<QString> lockedBy;            // Data on which computer has the project open
    qint32         saveCount   = 0;     // Meta data: number of saves
    qint32         autoCount   = 0;     // Meta data: number of automatic saves

    // Project Data
    QHash<QString, int> projTree;       // Holds all the items of the project
    QList<QString>      treeOrder;      // The order of the tree items on the tree view
    QList<QString>      treeRoots;      // The root items of the tree
    QString             trashRoot = ""; // The handle of the trash root folder
    QString             projPath  = ""; // The full path to where the currently open project is saved
    QString             projMeta  = ""; // The full path to the project's meta data folder
    QString             projDict  = ""; // The spell check dictionary
    QString             projFile  = ""; // The file name of the project main xml file
};

#endif // PROJECT_H
