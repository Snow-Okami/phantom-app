#include "frameless/include/widget.h"
#include "frameless/include/titlebar.h"

#include "ui_mainwindow.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindowForm)
{
    //Set up background here (taken care of by CSS style sheet)
    Widget::BackgroundSetup();
    //Set up titlebar here
    Widget::TitleBar(parent);
    //We must load the ui form AFTER we set up the title bar
    ui->setupUi(this); //this loads the ui on this widget
    //Connect up the
    ConnectSignals();
    //Setup any form widgets programmatically
    Widget::FormWidgetSetup();

    //QApplication::installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::TitleBar(QWidget *parent)
{
    //Create Title Widget
    titleWidget = new QWidget(this);
    titleWidget->setObjectName( "titleWidget" );

    titleLayout = new QHBoxLayout();
    titleLayout->setObjectName("titleLayout");
    titleLayout->setSpacing( 0 );
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setMargin(0);

    // Window title
    QLabel* titleLabel = new QLabel("Phantom Net");
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
    minimizeButton = new QPushButton( "", this );
    minimizeButton->setObjectName( "minimizeButton" );
    titleLayout->addWidget( minimizeButton );
    minimizeButton->setFocusPolicy(Qt::NoFocus);

    // Maximize
    maximizeButton = new QPushButton( "", this );
    maximizeButton->setObjectName( "maximizeButton" );
    titleLayout->addWidget( maximizeButton );
    maximizeButton->setFocusPolicy(Qt::NoFocus);
    maximizeButton->setCheckable(true);

    //titleLayout Close
    closeButton = new QPushButton( "", this );
    closeButton->setObjectName( "closeButton" );
    titleLayout->addWidget( closeButton );
    closeButton->setFocusPolicy(Qt::NoFocus);

    // Main panel layout
    mainGridLayout = new QGridLayout();
    mainGridLayout->setSpacing( 0 );
    mainGridLayout->setMargin( 0 );
    setLayout(mainGridLayout);

    // Central widget
    centralWidget = new QWidget(this);
    centralWidget->setObjectName( "centralWidget" );
    centralWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    // Main panel scroll area
    scrollArea = new QScrollArea( this );
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

    verticalLayout->addWidget(this);
    scrollArea->setFocusPolicy(Qt::NoFocus);
    this->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::NoFocus);
    show();
}

void Widget::BackgroundSetup()
{
    //Set a black background for funsies
    QPalette Pal(palette());
    QColor desysiaGrey = QColor(38, 38, 41, 255);
    Pal.setColor(QPalette::Background, desysiaGrey);
    setAutoFillBackground(true);
    setPalette(Pal);
}

void Widget::FormWidgetSetup()
{
    ui->mainLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
}

//bool Widget::eventFilter(QObject* /*object (Disable C4100 warning from VS compiler)*/, QEvent *event)
//{
////    if (event->type() == QEvent::KeyPress)
////    {
////        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
////        if(keyEvent->key() == Qt::Key_Return)
////        {
////            qDebug() << "Return pressed!";
////            return true;
////        }
////    }
////    return false;
//}

//void Widget::ConnectSignals()
//{
//    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_buttonPushed_clicked()));
//    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_buttonSetResult_clicked()));
//}

//void Widget::slot_buttonPushed_clicked()
//{
//    //auto child = std::make_unique<TestWindow>(_app, this);
//    //qDebug() << child->exec();
//    qDebug("smashed that like button");
//}

//void Widget::slot_buttonSetResult_clicked()
//{
//    //setResult(true);
//}

void Widget::ConnectSignals()
{
    connect(ui->loginBtn, SIGNAL(clicked()), this, SLOT(On_LoginButton_Clicked()));
}

void Widget::On_LoginButton_Clicked()
{
    qDebug("Login sent!");
}
