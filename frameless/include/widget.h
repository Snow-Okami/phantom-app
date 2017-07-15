#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QToolBar>

#include <QApplication>
#include <QHBoxLayout>
#include <QStyle>
#include <QLabel>
#include <QSizePolicy>
#include <QScrollArea>

#include <QMainWindow>
#include "ui_main.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    explicit Widget(QWidget *parent = 0);
    //Destructor
    ~Widget();

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
    void WidgetSetup();

signals:
//    bool eventFilter(QObject *, QEvent *event);

private slots:
    void On_LoginButton_Clicked();

private:
    Ui::MainWindowForm *ui;
};

#endif // WIDGET_H
