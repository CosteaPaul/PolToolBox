#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "session.h"
#include "qmessagebox.h"
#include "polsettings.h"
#include "qsettings.h"
#include "polcopy.h"
#include "polxmlparser.h"
#include "qdir.h"
#include "polruntool.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mRunner(NULL)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    //Get the config.xml file
    this->setCursor(Qt::WaitCursor);
    QSettings settings;
    QString locPath = settings.value("local","").toString();
    if (locPath.isEmpty()) {
        QMessageBox::information(this,"Path issue","Please configure local path");
        return;
    }
    //Copy config file
    if (!PolCopy::copyFromServer("config.xml",locPath)) {
        //Check if there is a config file already available.
        QDir local(locPath);
        if (local.exists("config.xml")) {
            QMessageBox::warning(this,"Warning","Unable to retrieve config.xml from server. Session will use an older local copy if it");
        }else {
            QMessageBox::information(this,"Error","Tools config file was not found. Make sure you have set all paths correctly or contact your ToolBox administrator");
        }
    }
    this->setCursor(Qt::ArrowCursor);

    //Parse config file
    PolXMLParser* myParser = new PolXMLParser(locPath+"config.xml");
    QStringList all = myParser->getToolsList();
    ui->listWidget_available->addItems(all);
    delete myParser;
}

void MainWindow::on_actionSettings_triggered()
{
    PolSettings* sett = new PolSettings(this);
    sett->exec();
}

void MainWindow::on_listWidget_available_doubleClicked(QModelIndex index)
{
    QString appName = ui->listWidget_available->selectedItems().at(0)->text();
    if (mRunner != NULL) {
        //Remove previous run options
        ui->verticalLayout->removeWidget(mRunner);
        delete mRunner;
        mRunner = NULL;
    }
    mRunner = new PolRunTool(this,appName);
    mRunner->setObjectName(QString::fromUtf8("runOptions"));
    ui->verticalLayout->addWidget(mRunner,1);
}
