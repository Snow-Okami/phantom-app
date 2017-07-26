#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QToolBar>

#include <QApplication>
#include <QHBoxLayout>
#include <QStyle>
#include <QLabel>
#include <QSizePolicy>
#include <QScrollArea>

#include <QKeyEvent>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QFile>

//Custom
#include "main/window/include/windowbase.h"
#include "ui_main.h"

//#include "main/sockets/socketengine.h"
#include "main/utilities/include/settings.h"

class MainWindow : public WindowBase
{
    Q_OBJECT
public:
    //Constructor
    explicit MainWindow(QWidget *parent = 0);
    //Destructor
    ~MainWindow();

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

protected:
    bool eventFilter(QObject *, QEvent *event) override;

signals:


private slots:
    void On_InstallButton_Clicked();
    void On_LocateButton_Clicked();

private:
    //Form - UI
    Ui::MainWindowForm *ui;
};

#endif // MAINWINDOW_H
