#include "main/window/include/windowbase.h"
//We must declare socket engine in the cpp file and not the header to avoid the issue
//Of circular dependancy
#include "main/sockets/socketengine.h"

WindowBase::WindowBase(QWidget *parent)
    : QWidget(parent)
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
}

WindowBase::~WindowBase()
{

}

void WindowBase::TitleBar(QWidget *parent)
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
    minimizeButton = new QPushButton( "", this );
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

void WindowBase::BackgroundSetup()
{

}

void WindowBase::FormWidgetSetup()
{

}

void WindowBase::UiSetup()
{

}

void WindowBase::EventSetup()
{

}

bool WindowBase::eventFilter(QObject* /*object (Disable C4100 warning from VS compiler)*/, QEvent *event)
{

}

void WindowBase::ConnectSignals()
{

}
