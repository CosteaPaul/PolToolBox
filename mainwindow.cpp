#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "session.h"
#include "qmessagebox.h"


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

void MainWindow::on_pushButton_clicked()
{
    Session* uppmax = Session::getInstance();
    uppmax->connect("pcostea@kalkyl.uppmax.uu.se");
    //Check is connected
    if (uppmax->getConnected())
        //Hide button!
        ui->pushButton->setVisible(false);

    uppmax->getProcess()->write("cd /bubo/proj/b2010052\n");
    uppmax->getProcess()->write("ls -1\n");
    uppmax->getProcess()->waitForReadyRead();
    //Find "toolbox" folder
    QString less = uppmax->getProcess()->readAllStandardOutput();
    QStringList folders = less.split('\n');
    if (folders.indexOf("toolbox") != -1)
        QMessageBox::information(this,"Good","All up and running");
    else
        QMessageBox::information(this,"Nope","No toolbox found for this project");
}
