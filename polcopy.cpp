#include "polcopy.h"
#include "qprocess.h"
#include "qsettings.h"

PolCopy::PolCopy()
{
}

bool PolCopy::copyToServer(QString localPath)
{
    //Get server and project ID
    QSettings settings;
    QString host = settings.value("connect","").toString();
    QString projId = settings.value("projID","").toString();

    //TODO: destination should not be UPPMAX specific
    QString destination = host+":/bubo/proj/"+projId+"/toolbox/temp/";

    QProcess* scp = new QProcess();
    QString app = "scp";
    scp->start(app,QStringList() << localPath << destination);

    if (!scp->waitForStarted()) {
        scp->close();
        delete scp;
        return false;
    }
    //Wait for copy to be done!
    scp->waitForFinished();
    //Get exit code
    int exit = scp->exitCode();
    if (exit != 0) {
        //Copy did not succeed.
        QString aa = scp->readAllStandardError();
    }
    delete scp;
    return true;

}

bool PolCopy::copyFromServer(QString fileName, QString localPath)
{
    //TODO: implement
    return false;
}
