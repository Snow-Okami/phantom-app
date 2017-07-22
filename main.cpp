#include <QApplication>
#include <QFile>

#include "main/window/include/windowbase.h"
#include "main/window/include/mainwindow.h"
#include "main/window/include/loginwindow.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "main/sockets/socketengine.h"

#ifdef _WIN32
#include "frameless/include/QWinWidget.h"
#else
#include "mainwindow.h"
#endif

#ifdef __APPLE__
#include "frameless/include/OSXHideTitleBar.h"
#endif

int main(int argc, char *argv[])
{
    //This has the app draw at HiDPI scaling on HiDPI displays, usually two pixels for every one logical pixel
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //This has QPixmap images use the @2x images when available
    //See this bug for more details on how to get this right: https://bugreports.qt.io/browse/QTBUG-44486#comment-327410
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    //A common feature is to save your app's geometry on close such that you can draw in the same place on relaunch
    //Thus this project supports specifying the X/Y/Width/Height in a cross-platform manner
    int windowXPos, windowYPos, windowWidth, windowHeight;
    windowXPos = 100;
    windowYPos = 100;
    windowWidth = 720;
    windowHeight = 540;

    //Style
    QFile stylesheet( ":/themes/desysia.css" );
    //Load style sheet and set it
    if ( stylesheet.open( QFile::ReadOnly ) )
    {
        QString styleSheet = stylesheet.readAll();
        app.setStyleSheet( styleSheet );
    }

//    MainWindow main;
//    MainWindow *mainPtr = &main;

    #ifdef _WIN32

    //On Windows, the widget needs to be encapsulated in a native window for frameless rendering
    //In this case, QWinWidget #includes "MainWindow.h", creates it, and adds it to a layout
    //QWinWidget w(QWinWidget::Main, true, false, 720, 540);

    QWinWidget l(QWinWidget::Login, false, true, 200, 250, 200, 250);
    l.setGeometry(200, 200, 200, 250);

    l.show();


//    QWinWidget m(QWinWidget::Main, false, true, 200, 250, 720, 540);
//    m.setGeometry(200, 200, 720, 540);

//    //m.show();
//    m.hide();

//    QWinWidget b(QWinWidget::Base, false, true, 200, 250);
//    b.setGeometry(200, 200, 250, 250);

//    b.show();


    #else

    //On OS X / Linux, the widget can handle everything itself so just create Widget as normal
    MainWindow w;

    #endif

    #ifdef __APPLE__

    //Then, hide the OS X title bar
    OSXHideTitleBar::HideTitleBar(w.winId());

    #endif

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(app);
    bool debug = parser.isSet(dbgOption);
    //Force Debug True
    debug = true;
    SocketEngine::Instance()->SetDebug(debug);

    //SocketEngine client(QUrl(QStringLiteral("ws://localhost:8080")), debug);
    //QObject::connect(&client, &SocketEngine::closed, &app, &SocketEngine::opened);

    //w.setGeometry(windowXPos, windowYPos, windowWidth, windowHeight);

    //w.show();
    return app.exec();
}
