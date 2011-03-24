#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "session.h"
#include "qmessagebox.h"
#include "polsettings.h"
#include "qsettings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

#include "QTime"
#include "polcopy.h"
#include "qdir.h"

void MainWindow::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    QSettings settings;
    QString locPath = settings.value("local","").toString();
    if (locPath.isEmpty()) {
        QMessageBox::information(this,"Path issue","Please configure local path");
        return;
    }
    //Copy config file
    PolCopy::copyFromServer("config.xml",locPath);
    this->setCursor(Qt::ArrowCursor);
    return;
    Session* uppmax = Session::getInstance();
    QString host = settings.value("connect","").toString();
    uppmax->connect(host);
    //Check is connected
    if (uppmax->getConnected())
        //Hide button!
        ui->pushButton->setVisible(false);
    else {
        QMessageBox::information(this,"Connection Problem","Unable to connect to the specified host. \nMake sure your settings are ok");
        return;
    }
    QStringList tools = uppmax->getAvailableTools(settings.value("projID","").toString());
    ui->listWidget_available->addItems(tools);

}

void MainWindow::on_actionSettings_triggered()
{
    PolSettings* sett = new PolSettings(this);
    sett->exec();
}
