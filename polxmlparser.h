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
private:
    QDomDocument doc;
};

#endif // POLXMLPARSER_H
