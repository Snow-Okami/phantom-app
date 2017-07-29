#include "main/window/include/loginwindow.h"
//We must declare socket engine in the cpp file and not the header to avoid the issue
//Of circular dependancy
#include "main/sockets/include/socketengine.h"

LoginWindow::LoginWindow(QWidget *parent)
    : WindowBase(parent),
      p_ParentWidget(parent),
      ui(new Ui::LoginWindowForm)
{
    //Set up background here (taken care of by CSS style sheet)
    BackgroundSetup();
    //Set up titlebar here
    TitleBar(parent);
    //We must load the ui form AFTER we set up the title bar
    UiSetup();
    //Connect up the
    ConnectSignals();
    //Setup any form widgets programmatically
    FormWidgetSetup();
    //Setup event listening
    EventSetup();
    //this->setAttribute(Qt::WA_TransparentForMouseEvents);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::TitleBar(QWidget *parent)
{
    //Create Title Widget
    titleWidget = new QWidget(parent);
    titleWidget->setObjectName( "titleWidget" );

    titleLayout = new QHBoxLayout();
    titleLayout->setObjectName("titleLayout");
    titleLayout->setSpacing( 0 );
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setMargin(0);

    // Window title
    QLabel* titleLabel = new QLabel("");
    titleLabel->setFixedWidth(160);
    titleLabel->setStyleSheet("background-color: none; color: #ffffff; border: none;");

    //Set it transparent to mouse events such that you can click and drag when moused over the label
    titleLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    //Create spacer widgets to keep the title centered
    QWidget* leftSpacer = new QWidget(titleWidget);
    QWidget* rightSpacer = new QWidget(titleWidget);

    //Set them transparent to mouse events + auto-expanding in size
    leftSpacer->setAttribute(Qt::WA_TransparentForMouseEvents);
    leftSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    leftSpacer->setStyleSheet("background-color: none; border: none;");
    rightSpacer->setAttribute(Qt::WA_TransparentForMouseEvents);
    rightSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    rightSpacer->setStyleSheet("background-color: none; border: none;");

    //Add spacers & title label
    titleLayout->addWidget(leftSpacer);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(rightSpacer);

    //Old method of adding space before buttons
    //titleLayout->addStretch();

    // System buttons
    // Minimize
    minimizeButton = new QPushButton( "", parent );
    minimizeButton->setObjectName( "minimizeButton" );
    titleLayout->addWidget( minimizeButton );
    minimizeButton->setFocusPolicy(Qt::NoFocus);

    // Maximize
//    maximizeButton = new QPushButton( "", this );
//    maximizeButton->setObjectName( "maximizeButton" );
//    titleLayout->addWidget( maximizeButton );
//    maximizeButton->setFocusPolicy(Qt::NoFocus);
//    maximizeButton->setCheckable(true);

    //titleLayout Close
    closeButton = new QPushButton( "", parent );
    closeButton->setObjectName( "closeButton" );
    titleLayout->addWidget( closeButton );
    closeButton->setFocusPolicy(Qt::NoFocus);

    // Main panel layout
    mainGridLayout = new QGridLayout();
    mainGridLayout->setSpacing( 0 );
    mainGridLayout->setMargin( 0 );
    setLayout(mainGridLayout);

    // Central widget
    centralWidget = new QWidget(parent);
    centralWidget->setObjectName( "centralWidget" );
    centralWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    // Main panel scroll area
    scrollArea = new QScrollArea( parent );
    scrollArea->setWidgetResizable( true );
    scrollArea->setObjectName( "mainPanelScrollArea" );
    scrollArea->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    // Vertical layout example
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing( 0 );
    verticalLayout->setMargin( 0 );
    //verticalLayout.setAlignment( Qt::AlignTop );
    //verticalLayout.setAlignment(Qt::AlignCenter);
    //verticalLayout.addLayout( horizontalLayout );

    // Show
    titleWidget->setLayout( titleLayout );
    titleWidget->setLayout( verticalLayout );
    scrollArea->setWidget( centralWidget );
    mainGridLayout->addWidget( titleWidget );
    //mainGridLayout->addWidget( &centralWidget );
    mainGridLayout->addWidget( scrollArea );

    verticalLayout->addWidget(parent);
    scrollArea->setFocusPolicy(Qt::NoFocus);
    this->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::NoFocus);
    show();
}

void LoginWindow::BackgroundSetup()
{
    //Set a black background for funsies
    QPalette Pal(palette());
    QColor desysiaGrey = QColor(38, 38, 41, 255);
    Pal.setColor(QPalette::Background, desysiaGrey);
    setAutoFillBackground(true);
    setPalette(Pal);
}

void LoginWindow::FormWidgetSetup()
{
    //Makes the label pass mouse events, this avoids the label accidentally consuming events
    //ui->mainLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents);
    //ui->verticalLayout->setAttribute(Qt::WA_TransparentForMouseEvents);
    //ui->horizontalLayout->setAttribute(Qt::WA_TransparentForMouseEvents);
    //ui->verticalLayoutWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void LoginWindow::UiSetup()
{
    //this loads the ui on this widget
    ui->setupUi(this);
}

void LoginWindow::EventSetup()
{
    installEventFilter(this);
    //This sets up receiving events from the socket engine
    SocketEngine::Instance()->loginWindow = this;
}

bool LoginWindow::eventFilter(QObject* /*object (Disable C4100 warning from VS compiler)*/, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Return)
        {
            qDebug() << "Return pressed!";
            return true;
        }
    }
    return false;
}

void LoginWindow::ConnectSignals()
{
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(On_LoginButton_Clicked()));
    connect(ui->showPasswordButton, SIGNAL(clicked()), this, SLOT(On_ShowPasswordButton_Clicked()));
    connect(ui->passwordInput, SIGNAL(editingFinished()), this, SLOT(On_PasswordLineEdit_Ended()));
    connect(ui->passwordInput, SIGNAL(returnPressed()), this, SLOT(SendLogin()));
    connect(ui->createAccountButton, SIGNAL(clicked()), this, SLOT(On_CreateAccount_Clicked()));
    connect(ui->forgotButton, SIGNAL(clicked()), this, SLOT(On_Forgot_Clicked()));
    //NETWORK

    ui->showPasswordButton->setCheckable(true);
}

void LoginWindow::On_LoginButton_Clicked()
{
    SendLogin();
}

//Switches the password field from unseen, to seen, also switches the icon
void LoginWindow::On_ShowPasswordButton_Clicked()
{
    if(ui->passwordInput->echoMode() == QLineEdit::Normal)
    {
        ui->showPasswordButton->setIcon(QIcon(":/Eye_Invisible.png"));
        ui->showPasswordButton->setIconSize(QSize(16,16));
        //ui->showPasswordButton->setStyleSheet( "#showPasswordButton {image: url(:/Eye_Invisible.png);} #showPasswordButton:hover { image: url(:/Eye_Invisible.png); }" );
        ui->passwordInput->setEchoMode(QLineEdit::Password);
    }

    else if(ui->passwordInput->echoMode() == QLineEdit::Password)
    {
        ui->showPasswordButton->setIcon(QIcon(":/Eye_Visible.png"));
        ui->showPasswordButton->setIconSize(QSize(16,16));
        //ui->showPasswordButton->setStyleSheet( "#showPasswordButton {image: url(:/Eye_Visible.png);} #showPasswordButton:hover { image: url(:/Eye_Visible.png); }" );
        ui->passwordInput->setEchoMode(QLineEdit::Normal);
    }
}

void LoginWindow::On_CreateAccount_Clicked()
{
//    QString link = "http://www.google.com";
//    QDesktopServices::openUrl(QUrl(link));
    SocketEngine::Instance()->SendFriendUser("goon");
}

void LoginWindow::On_Forgot_Clicked()
{
    QString link = "http://www.youtube.com";
    QDesktopServices::openUrl(QUrl(link));
}

void LoginWindow::On_PasswordLineEdit_Ended()
{
    //qDebug("checking your input");
}

void LoginWindow::SendLogin()
{
    ui->loginButton->setEnabled(false);
    int addedHeight = 500;
//    p_ParentWidget->setMinimumHeight(this->height() + addedHeight);
//    p_ParentWidget->setMaximumHeight(this->height() + addedHeight);

//    p_ParentWidget->setGeometry(p_ParentWidget->x(), p_ParentWidget->y(), p_ParentWidget->width() + addedHeight, p_ParentWidget->height() + addedHeight);
//    p_ParentWidget->update();
//    p_ParentWidget->updateGeometry();
    this->parentWidget()->setGeometry(p_ParentWidget->x(), p_ParentWidget->y(), p_ParentWidget->width() + addedHeight, p_ParentWidget->height() + addedHeight);

    //QLabel *response = new QLabel("...Logging in...");
    //response->setMinimumHeight(addedHeight);
    //ui->verticalLayout->insertWidget(4, response);

    ui->loginButton->setText("...Logging in...");

//    SocketEngine::Instance()->SendLogin(ui->emailInput->text(), ui->passwordInput->text());
//    //If login takes longer than threshold, assume login has failed
//    QTimer::singleShot(5000, this, SLOT(LoginFailed()));

    QJsonObject json;
    json["username"] = ui->emailInput->text();
    json["password"] = ui->passwordInput->text();
    QJsonDocument jsonDoc(json);

    QUrl url("http://localhost:3000/users/authenticate");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray data = jsonDoc.toJson();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(ReplyFinished(QNetworkReply *)));

    //qDebug() << "Sync" << QString::fromUtf8(data.data(), data.size());

    manager->post(request, data);
}

void LoginWindow::ReplyFinished(QNetworkReply *reply)
{
    //Convert response to readable byte array
    QByteArray bts = reply->readAll();
    //Convert response to json object we can query again
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bts, &err);
    //Set up catch vars
    bool d_success;
    QString d_token;
    //Get values from json object
    if(jsonDoc.isObject())
    {
        QJsonObject obj = jsonDoc.object();
        QJsonValue success = obj.value("success");
        QJsonValue token = obj.value("token");
        if (!success.isUndefined()) {
            if (success.isBool()) {
                d_success = success.toBool();
                qDebug() << d_success;
            }
        }
        if (!token.isUndefined()) {
            if (token.isString()) {
                d_token = token.toString();
                qDebug() << d_token;
            }
        }
    }

    ReceiveLogin(d_success, d_token);

    //Clean up reply
    reply->deleteLater();
    //Full reply
//    QString strReply(bts);
//    qDebug() << strReply;
}

void LoginWindow::LoginFailed()
{
    //This code runs no matter what to check for time outs
    //If we have already logged in, we shouldn't continue
    if(loggedIn || loginResponseReceived) return;

    ui->loginButton->setText("...Login Timed Out!...");
}

void LoginWindow::ReceiveLogin(bool successful, QString token)
{
    loginResponseReceived = true;

    ui->loginButton->setEnabled(true);

    if(successful)
    {
        loggedIn = true;
        ui->loginButton->setText("...Logging Successful!...");
        SocketEngine::Instance()->SetToken(token);
        SocketEngine::Instance()->Connect();

//        SocketEngine::Instance()->mainWindow->show();
//        SocketEngine::Instance()->mainWindow->parentWidget()->show();
//        this->hide();
//        this->parentWidget()->hide();
    }
    else
    {
        ui->loginButton->setText("...Login Failed!...");
    }
}

//void LoginWindow::ReceiveLogin(bool successful, QString response)
//{
//    loginResponseReceived = true;

//    ui->loginButton->setEnabled(true);

//    if(successful)
//    {
//        loggedIn = true;
//        ui->loginButton->setText("...Logging Successful!...");
////        SocketEngine::Instance()->mainWindow->show();
////        SocketEngine::Instance()->mainWindow->parentWidget()->show();
////        this->hide();
////        this->parentWidget()->hide();
//    }
//    else
//    {
//        ui->loginButton->setText("...Login Failed!...");
//    }
//}

void LoginWindow::customEvent(QEvent * event)
{
    // When we get here, we've crossed the thread boundary and are now
    // executing in the Qt object's thread
    if(event->type() == LOGIN_RESPONSE_EVENT)
    {
        HandleLoginResponseEvent(static_cast<LoginResponseEvent *>(event));
    }

    // use more else ifs to handle other custom events
}

void LoginWindow::HandleLoginResponseEvent(const LoginResponseEvent *event)
{
    // Now you can safely do something with your Qt objects.
    // Access your custom data using event->GetSuccess() etc.
    ReceiveLogin(event->GetSuccess(), event->GetResponse());

}
