#include "projxmlreader.h"

#include <QDebug>

ProjXMLReader::ProjXMLReader() {}
ProjXMLReader::~ProjXMLReader() {}

int ProjXMLReader::readProjectXML(QFile* projFile, bool overrideLock) {

    QXmlStreamReader xml;
    xml.setDevice(projFile);

    if (xml.readNextStartElement() && xml.name() == "novelWriterXML") {

        auto attr = xml.attributes();

        if (!attr.hasAttribute("appVersion")) {
            qCritical() << "Project XML does not contain the appVersion attribute.";
            return 1;
        }
        if (!attr.hasAttribute("hexVersion")) {
            qCritical() << "Project XML does not contain the hexVersion attribute.";
            return 1;
        }
        if (!attr.hasAttribute("fileVersion")) {
            qCritical() << "Project XML does not contain the fileVersion attribute.";
            return 1;
        }

        auto appVersion  = attr.value("", "appVersion");
        auto hexVersion  = attr.value("", "hexVersion");
        auto fileVersion = attr.value("", "fileVersion");

        qDebug() << "Project file appVersion:"  << appVersion;
        qDebug() << "Project file hexVersion:"  << hexVersion;
        qDebug() << "Project file fileVersion:" << fileVersion;

        // Parse the main categories
        while (xml.readNextStartElement()) {
            if (xml.name() == "project") {
                if (!unpackProjectXML(&xml)) {
                    return 1;
                }
            } else if (xml.name() == "settings") {
                if (!unpackSettingsXML(&xml)) {
                    return 1;
                }
            } else if (xml.name() == "content") {
                if (!unpackContentXML(&xml)) {
                    return 1;
                }
            } else {
                xml.skipCurrentElement();
                qWarning() << "Unknown XML entry:" << xml.name();
            }
        }

        // qDebug() << xml.tokenString() << xml.name() << xml.text();
        // qDebug() << xml.

        if (xml.tokenType() == QXmlStreamReader::Invalid) {
            qDebug() << "Closing XML";
            xml.readNext();
        }
    
        if (xml.hasError()) {
            xml.raiseError();
            qDebug() << xml.errorString();
        }
    }

    return 0;
}

bool ProjXMLReader::unpackProjectXML(QXmlStreamReader* xml) {

    qDebug() << "Unpacking XML <project>";

    return true;
}

bool ProjXMLReader::unpackSettingsXML(QXmlStreamReader* xml) {

    qDebug() << "Unpacking XML <settings>";

    return true;
}

bool ProjXMLReader::unpackContentXML(QXmlStreamReader* xml) {

    qDebug() << "Unpacking XML <content>";

    return true;
}
