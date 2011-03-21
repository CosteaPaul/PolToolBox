#include "session.h"

Session* Session::m_pInstance = 0;

Session* Session::getInstance()
{
    if (!m_pInstance)
        m_pInstance = new Session();

    return m_pInstance;
}

Session::Session()
    :isConnected(false),
    m_pSsh(0)
{

}

bool Session::connect(QString host)
{
    if (isConnected) {
        //Must disconnect before connecting;
        return false;
    }

    m_pSsh = new QProcess();
    QString app = "ssh";
    m_pSsh->start(app,QStringList() << host);
    if (!m_pSsh->waitForStarted()) {
        m_pSsh->close();
        delete m_pSsh;
        return false;
    }
    //At this point, OpenSSH will cause a password dialog to pop-up. (some tunelling "junk")
    //Try to write something to ssh and wait for read
    m_pSsh->write("ls -all\n");

    //Wait for connection to be estblished
    if (!m_pSsh->waitForReadyRead()) {
        m_pSsh->close();
        delete m_pSsh;
        return false;
    }

    QByteArray res = m_pSsh->readAllStandardOutput();
    if (res.length() > 0) {
        //Got something! Connection is UP!
        isConnected = true;
    }

    return isConnected;
}

QString Session::runCommand(const QString& cmd, QStringList args)
{
    if (!m_pSsh)
        return "";
    QString fullCommand = cmd;
    for (int i=0 ; i<args.count(); ++i) {
        fullCommand += " "+args[i];
    }
    fullCommand += "\n";
    //Run the command
    m_pSsh->write(fullCommand.toLocal8Bit());
    if (!m_pSsh->waitForReadyRead()) {
        //Something went wrong
        return "";
    } else {
        QString res = m_pSsh->readAllStandardOutput();
        return res;
    }
}

QStringList Session::getAvailableTools(QString projID)
{
    if (!m_pSsh) {
        return QStringList();
    }
    //TODO: path should be independent of UPPMAX file system.
    QString path = "/bubo/proj/"+projID;
    runCommand("cd",QStringList()<<path);
    QString less = runCommand("ls -1");
    QStringList folders = less.split('\n');
    if (folders.indexOf("toolbox") != -1) {
        //Populate tools list.
        runCommand("cd",QStringList()<<"toolbox");
        QString less = runCommand("ls -1");
        QStringList tools = less.split('\n');
        return tools;
    } else
        return QStringList();
}
