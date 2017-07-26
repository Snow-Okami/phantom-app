#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QToolBar>

#include <QApplication>
#include <QHBoxLayout>
#include <QStyle>
#include <QLabel>
#include <QSizePolicy>
#include <QScrollArea>

#include <QObject>
#include <QDebug>

#include <QDesktopServices>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QTimer>

#include <QKeyEvent>
#include <QEvent>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonObject>
#include <QJsonDocument>
//Custom
#include "main/window/include/windowbase.h"
#include "ui_login.h"

#include "main/utilities/include/customevents.h"
//#include "main/sockets/socketengine.h"

class LoginWindow : public WindowBase
{
    Q_OBJECT
public:
    //Constructor
    explicit LoginWindow(QWidget *parent = 0);
    //Destructor
    ~LoginWindow();

    //Buttons
    QPushButton *minimizeButton = nullptr;
    QPushButton *maximizeButton = nullptr;
    QPushButton *closeButton = nullptr;

    //Base layouts for buttons & bar Layouts
    QHBoxLayout *layout = nullptr;
    QVBoxLayout *layoutBase = nullptr;
    QHBoxLayout *toolBarLayout = nullptr;

    //Main Window Title
    QLabel *windowTitle = nullptr;

    //Main Widgets
    QWidget *titleWidget = nullptr;
    QWidget *centralWidget = nullptr;
    QScrollArea *scrollArea = nullptr;

    //Main Layouts
    QHBoxLayout *titleLayout = nullptr;
    QVBoxLayout *verticalLayout = nullptr;
    QVBoxLayout *horizontalLayout = nullptr;
    QGridLayout *mainGridLayout = nullptr;

public:
    void TitleBar(QWidget *parent);
    void BackgroundSetup();
    void ConnectSignals();
    void FormWidgetSetup();
    void UiSetup();
    void EventSetup();

public:
    void ReceiveLogin(bool successful, QString response);

protected:
    bool eventFilter(QObject *, QEvent *event) override;

signals:


private slots:
    void On_LoginButton_Clicked();
    void On_ShowPasswordButton_Clicked();
    void On_CreateAccount_Clicked();
    void On_Forgot_Clicked();
    void On_PasswordLineEdit_Ended();
    void SendLogin();
    void LoginFailed();
    void ReplyFinished(QNetworkReply *reply);

private:
    //Form - UI
    Ui::LoginWindowForm *ui;

    QWidget *p_ParentWidget;

    bool loggedIn;
    bool loginResponseReceived;

//EVENTS
public:
    //void postMyCustomEvent(const int customData1, const int customData2);

protected:
    void customEvent(QEvent *event); // This overrides QObject::customEvent()

private:
    void HandleLoginResponseEvent(const LoginResponseEvent *event);
    //void handleMyCustomEvent(const MyCustomEvent *event);
};

#endif // LOGINWINDOW_H
