#ifndef SESSION_H
#define SESSION_H
#include "QProcess"

class Session
{

public:

    typedef enum Errors {
        SESSION_DOWN = 0,
    };

    static Session* getInstance();
    bool getConnected(){
        return isConnected;
    };

    /**
      * @brief Connect seesion to specified host
      * @arg host - String of host server
      * @returns true if connection succeded, false otherwise
      */
    bool connect(QString host);

    /**
      * @brief Run command on host server.
      * @arg cmd -  Command to run.
      *             If command is not in PATH, preceding ./ and full path must be given.
      * @arg args - Arguements to be passed to the command.
      * @returns QString representing the full output of the command
      * @reentrant No
      */
    QString runCommand(const QString& cmd, QStringList args = QStringList());

    /**
      * @brief Find all available tools in host toolbox
      * @arg projID - Name of projID under which the toolbox exists
      * @returns QStringList containg names of all available tools
      */
    QStringList getAvailableTools(QString projID);

    /**
      * @brief Get the QProcess underlying current session
      * @returns QProcess* of current session
      */
    QProcess* getProcess(){ return m_pSsh; };

private:
    Session();
    Session(Session const&){};
    Session &operator=(Session const&){};
    static Session* m_pInstance;

    //Operational stuff
    QProcess* m_pSsh;

    bool isConnected;

};

#endif // SESSION_H
