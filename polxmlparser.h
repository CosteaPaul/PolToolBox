#ifndef POLXMLPARSER_H
#define POLXMLPARSER_H

#include <QtXml/QDomDocument>

class PolXMLParser
{
public:
    PolXMLParser(QString configFile);

    /**
      * @brief Return the tools list from the config file
      * @returns StringList of all available tools
      */
    QStringList getToolsList();

    QString getAuthor(QString appName);
    QString getDescription(QString appName);
    QDomNodeList getOptions(QString appName);
    QDomNodeList getParameters(QString appName);

private:
    QDomElement getNodeOfAppName(QString appName);

    QDomDocument doc;
};

#endif // POLXMLPARSER_H
