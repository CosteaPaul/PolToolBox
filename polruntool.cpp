#include "polruntool.h"
#include "ui_polruntool.h"
#include <QSettings>
#include <QCheckBox>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QLineEdit>

PolRunTool::PolRunTool(QWidget *parent, QString appName) :
    QToolBox(parent),
    ui(new Ui::PolRunTool),
    m_pParser(NULL)
{
    ui->setupUi(this);
    //Create parser
    QSettings settings;
    QString locPath = settings.value("local","").toString();
    m_pParser = new PolXMLParser(locPath+"config.xml");

    //Load data
    ui->label_Author->setText(m_pParser->getAuthor(appName));
    ui->text_Description->setText(m_pParser->getDescription(appName));

    //Build options tab
    QDomNodeList optionList = m_pParser->getOptions(appName);
    if (optionList.size() > 0) {
        //Create UI of all options
        for (int i=0; i<optionList.size(); ++i)
            buildFromXMLOption(optionList.at(i).toElement());
    } else {
        //Hide options tab
        ui->page_Options->setShown(false);
    }

    //Build parameters tab
    QDomNodeList paramList = m_pParser->getParameters(appName);
    if (paramList.size() > 0) {
        //Create UI of all parameters
        for (int i=0; i<optionList.size(); ++i)
            buildFromXMLParam(optionList.at(i).toElement());
    } else { //Hide parameters tab
        ui->page_Parameters->setShown(false);
    }

    setCurrentIndex(0);
}

/**
  * @brief: Build UI element for required parameter
  * @returns: True if success, false otherwise
  */
bool PolRunTool::buildFromXMLParam(QDomElement param)
{
    QString name = param.toElement().text();
    //Create line edit box
    QLabel* label = new QLabel(name,this);
    QLineEdit* edit = new QLineEdit(this);
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    QSpacerItem* s = new QSpacerItem(20,10,QSizePolicy::Minimum, QSizePolicy::Expanding);
    hLayout->addWidget(label);
    hLayout->addWidget(edit);
    hLayout->addItem(s);
    ui->layout_Parameters->addLayout(hLayout);
    return true;
}

/**
  * @brief: Build UI element for option. Will created a
  * different type of control based on the 'type' of option.
  * @returns: True if success, false otherwise
  */
bool PolRunTool::buildFromXMLOption(QDomElement node)
{
    //Get type
    QDomNodeList l = node.elementsByTagName("type");
    if (l.size() < 1)
        //Something went wrong...
        return false;
    QString type = l.at(0).toElement().text();

    //Get key
    l = node.elementsByTagName("key");
    if (l.size() < 1)
        //Something went wrong...
        return false;
    QString key = l.at(0).toElement().text();

    //Get default
    l = node.elementsByTagName("default");
    if (l.size() < 1)
        //Something went wrong...
        return false;
    QString def = l.at(0).toElement().text();

    //Get description
    l = node.elementsByTagName("description");
    if (l.size() < 1)
        //Something went wrong...
        return false;
    QString descr = l.at(0).toElement().text();

    if (type == "bool") {
        //Add checkbox
        QCheckBox* c = new QCheckBox(descr,this);
        //Set default
        c->setChecked(def.compare("True",Qt::CaseInsensitive) == 0);
        ui->layout_Options->addWidget(c);
    } else if (type == "int") {
        //Add lable + edit box
        QLabel* label = new QLabel(descr,this);
        QLineEdit* edit = new QLineEdit(this);
        edit->setText(def);
        //Create horizontal layout for the lable + text box
        QHBoxLayout* hLayout = new QHBoxLayout(this);
        QSpacerItem* s = new QSpacerItem(20,10,QSizePolicy::Minimum, QSizePolicy::Expanding);
        hLayout->addWidget(label);
        hLayout->addWidget(edit);
        hLayout->addItem(s);
        //Add horizontal layout containing the lable and text box to the overall vertical layout of the widget
        ui->layout_Options->addLayout(hLayout);
    }

    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->layout_Options->addItem(spacer);
    return true;
}

PolRunTool::~PolRunTool()
{
    if (m_pParser != NULL)
        delete m_pParser;
    delete ui;
}
