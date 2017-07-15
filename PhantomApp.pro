#-------------------------------------------------
#
# Project created by QtCreator 2017-07-13T00:23:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhantomApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    frameless/src/titlebar.cpp \
    frameless/src/widget.cpp \
    main/window/src/mainwindow.cpp \
    main/utilities/src/debug.cpp \
    main/utilities/src/utilities.cpp

HEADERS += \  
    frameless/include/titlebar.h \
    frameless/include/widget.h \
    main/window/include/mainwindow.h \
    main/utilities/include/utilities.h

FORMS += \
    mainwindow.ui \
    main.ui

DISTFILES += \
    themes/desysia.css

RESOURCES += \
    application.qrc

#CONFIG += static

#CONFIG += console

win32 {
    # Only include / compile these files on Windows
    SOURCES += \
        frameless/src/qwinwidget.cpp \
        frameless/src/winnativewindow.cpp

    HEADERS += \
        frameless/include/qwinwidget.h \
        frameless/include/winnativewindow.h

    LIBS += -L"C:\Program Files\Microsoft SDKs\Windows\v7.1\Lib" \
        -ldwmapi \
        -lgdi32
}

mac {
    # Only include / compile these files on OS X
    OBJECTIVE_SOURCES += \
        frameless/include/OSXHideTitleBar.mm
    HEADERS  += \
        frameless/include/OSXHideTitleBar.h

    # Additionally include Cocoa for OS X code

    LIBS += -framework Foundation -framework Cocoa
    INCLUDEPATH += /System/Library/Frameworks/Foundation.framework/Versions/C/Headers
}
