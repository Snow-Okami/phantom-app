#ifndef SOCKETENGINE_H
#define SOCKETENGINE_H

#include <QObject>
#include <QWebSocket>
#include <QDebug>
#include <QEvent>
//CUSTOM
#include "main/utilities/include/utilities.h"
#include "main/utilities/include/customevents.h"
//WINDOWS
#include "main/window/include/loginwindow.h"
#include "main/window/include/mainwindow.h"
#include "main/window/include/windowbase.h"

class SocketEngine : public QObject
{
    Q_OBJECT
public:
    //Constructor
    SocketEngine(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);
    //Destructor
    ~SocketEngine();

    //Singleton
    static SocketEngine *Instance()
    {
        if (!s_instance)
          s_instance = new SocketEngine(QUrl(QStringLiteral("ws://localhost:8080")), true);
        return s_instance;
    }
    //Debugging
    void SetDebug(bool value);
    void SetToken(QString token);

    //Windows instances for event calling
    LoginWindow *loginWindow;
    MainWindow *mainWindow;
    WindowBase *windowBase;

public:
    void Connect();
    void CloseConnection();
    void SendMessage(QString message);
    void SendCommand(QString command, QString message);

    void SendLogin(QString username, QString password);
    void SendFriendUser(QString friendname);

    void LoginResponse(bool successful, QString response);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);

private:
    static SocketEngine *s_instance;
    QWebSocket m_webSocket;
    QUrl m_url;
    QString m_token;
    bool m_debug;

//EVENTS
public:
    void SendLoginResponseEvent(const bool success, const QString response);

protected:


private:

};

#endif // SOCKETENGINE_H
