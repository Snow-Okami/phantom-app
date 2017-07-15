#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QToolBar>

#include <QApplication>
#include <QHBoxLayout>
#include <QStyle>
#include <QLabel>

#include "ui_main.h"

class TitleBar
{
public:
    explicit TitleBar(QWidget *parent = 0);

    void Setup();

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

private:
    Ui::MainWindowForm *ui;

signals:

public slots:
};

#endif // TITLEBAR_H
