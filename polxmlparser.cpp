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

QString PolXMLParser::getAuthor(QString appName)
{
    QString author = "";

    QDomElement a = getNodeOfAppName(appName);
    if (a.isNull())
        return author;

    QDomNodeList l = a.elementsByTagName("author");
    if (l.size() != 1)
        return author;

    return l.at(0).toElement().text();
}

QDomNodeList PolXMLParser::getOptions(QString appName)
{
    QDomElement d = getNodeOfAppName(appName);
    if (d.isNull())
        return QDomNodeList();

    QDomNodeList l = d.elementsByTagName("option");
    return l;
}

QString PolXMLParser::getDescription(QString appName)
{
    QString descr = "";

    QDomElement d = getNodeOfAppName(appName);
    if (d.isNull())
        return descr;

    QDomNodeList l = d.elementsByTagName("description");
    if (l.size() < 1)
        return descr;

    return l.at(0).toElement().text();
}

QDomElement PolXMLParser::getNodeOfAppName(QString appName)
{
    QDomElement root = doc.documentElement();
    if (root.tagName() != "PolToolBox")
        return QDomElement();

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
                if (name == appName)
                    return e;
            }
        }
        n = n.nextSibling();
    }

    return QDomElement();
}
