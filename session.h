#ifndef SESSION_H
#define SESSION_H
#include "QProcess"

class Session
{

public:
    static Session* getInstance();
    bool getConnected(){
        return isConnected;
    };

    bool connect(QString host);

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
