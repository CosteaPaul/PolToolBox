#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("PaulIgor");
    QCoreApplication::setOrganizationDomain("github.com");
    QCoreApplication::setApplicationName("PolToolBox");
    MainWindow w;
    w.show();
    return a.exec();
}
