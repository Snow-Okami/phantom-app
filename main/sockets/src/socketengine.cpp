#include "main/sockets/include/socketengine.h"

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.
SocketEngine *SocketEngine::s_instance = 0;

SocketEngine::SocketEngine(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
    {
        qDebug() << "SocketEngine Created";
        qDebug() << "WebSocket Server:" << url;
    }

    connect(&m_webSocket, &QWebSocket::connected, this, &SocketEngine::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &SocketEngine::onDisconnected);

    //m_webSocket.open(QUrl(url));
}

SocketEngine::~SocketEngine()
{
    if (m_debug)
        qDebug() << "SocketEngine Destroyed";
}

void SocketEngine::Connect()
{
    QNetworkRequest request(m_url);

    request.setRawHeader(QString("token").toLocal8Bit(), m_token.toLocal8Bit());

    m_webSocket.open(request);
}

void SocketEngine::SetDebug(bool value)
{
    m_debug = value;
}

void SocketEngine::SetToken(QString token)
{
    m_token = token;
}

void SocketEngine::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";

    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &SocketEngine::onTextMessageReceived);
}

void SocketEngine::onDisconnected()
{
    if (m_debug)
        qDebug() << "WebSocket Disconnected";
}

void SocketEngine::onTextMessageReceived(QString message)
{
    qDebug() << "Message Received:" << message;
    if (m_debug)
        qDebug() << "Message Received:" << message;
    std::string command;
    //Parse arguments, get back arguements without the command at the beginning, pass in our command by reference
    std::string argsCmd = Utilities::ParseCommand(message, *(new QString("%")), command);
    //Get a list of our arguments using our delimiters to seperate
    std::vector<std::pair<std::string, std::string>> arguments = Utilities::ParseArguments(Utilities::StringToQString(argsCmd), *(new QString("|")),*(new QString(":")));

    if(command == "Login")
    {
        LoginResponse(Utilities::StringToBoolean(arguments[0].second), Utilities::StringToQString(arguments[1].second));
    }
}

void SocketEngine::CloseConnection()
{
    m_webSocket.close();
}

void SocketEngine::LoginResponse(bool successful, QString response)
{
    SendLoginResponseEvent(successful, response);
    qDebug() << "Login Response received:" << successful << " " << response;
    if (m_debug)
        qDebug() << "Login Response received:" << successful << " " << response;
}

void SocketEngine::SendMessage(QString message)
{
    m_webSocket.sendTextMessage(message);

    if (m_debug)
        qDebug() << "Message Sent:" << message;
}

void SocketEngine::SendCommand(QString command, QString message)
{
    QString formattedMessage = QString("%1%%2").arg(command).arg(message);

    m_webSocket.sendTextMessage(formattedMessage);

    if (m_debug)
        qDebug() << "Message Sent:" << formattedMessage;
}

void SocketEngine::SendLogin(QString username, QString password)
{
    //Should we hash the apssword before sending?
    QString loginDetails = QString("%1:%2").arg(username).arg(password);
    SendCommand(QString("login"), loginDetails);
}

void SocketEngine::SendFriendUser(QString friendname)
{
    //Should we hash the apssword before sending?
    QString loginDetails = QString("friend:%2").arg(friendname);
    SendCommand(QString("frienduser"), loginDetails);
}

void SocketEngine::SendLoginResponseEvent(const bool success, const QString response)
{
    // This method (SendLoginResponseEvent) can be called from any thread
    QApplication::postEvent(loginWindow, new LoginResponseEvent(success, response));
}
