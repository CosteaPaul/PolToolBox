#include "polxmlparser.h"
#include <QFile>
#include <QStringList>
#include <QDebug>

PolXMLParser::PolXMLParser(QString configFile)
{
    QFile file(configFile);
    if (file.open( QFile::ReadOnly ))
        doc.setContent(&file);

    //Discard file since it was already loaded by DOMDocument
    file.close();
}

QStringList PolXMLParser::getToolsList()
{
    QStringList tools;
    QDomElement root = doc.documentElement();
    if (root.tagName() != "PolToolBox")
        return tools;

    //Get tools
    QDomNode n = root.firstChild();
    while ( !n.isNull() ){
        QDomElement e = n.toElement();
        if (!e.isNull()) {
            if (e.tagName() == "tool") {
                QDomNodeList lst = e.elementsByTagName("name");
                if (lst.size() != 1) {
                    qDebug() << "PolXMLParser::getToolsList : Enoutered multiple names for same tool!";
                }
                QString name = lst.at(0).toElement().text();
                tools << name;
            }
        }
        n = n.nextSibling();
    }

    return tools;
}
