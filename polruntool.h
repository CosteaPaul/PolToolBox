#ifndef POLRUNTOOL_H
#define POLRUNTOOL_H

#include <QToolBox>
#include <QVBoxLayout>
#include "polxmlparser.h"

namespace Ui {
    class PolRunTool;
}

class PolRunTool : public QToolBox
{
    Q_OBJECT

public:
    explicit PolRunTool(QWidget *parent, QString appName);
    ~PolRunTool();

private:
    bool buildFromXMLOption(QDomElement opt);
    bool buildFromXMLParam(QDomElement param);

    Ui::PolRunTool *ui;
    PolXMLParser *m_pParser;

};

#endif // POLRUNTOOL_H
