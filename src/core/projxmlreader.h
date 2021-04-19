#ifndef PROJXMLREADER_H
#define PROJXMLREADER_H

#include "collett.h"

#include <QFile>
#include <QXmlStreamReader>

class ProjXMLReader
{

public:
    ProjXMLReader();
    ~ProjXMLReader();

    // Class Methods
    int readProjectXML(QFile* projFile, bool overrideLock=false);

private:

    // Methods
    bool unpackProjectXML(QXmlStreamReader* xml);
    bool unpackSettingsXML(QXmlStreamReader* xml);
    bool unpackContentXML(QXmlStreamReader* xml);

};

#endif // PROJXMLREADER_H
