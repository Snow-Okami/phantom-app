#ifndef WINDOWBASE_H
#define WINDOWBASE_H

#include <QWidget>
#include <QPushButton>
#include <QToolBar>

#include <QApplication>
#include <QHBoxLayout>
#include <QStyle>
#include <QLabel>
#include <QSizePolicy>
#include <QScrollArea>

#include <QDebug>
#include <QKeyEvent>

//Custom
//#include "main/sockets/socketengine.h"

class WindowBase : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    explicit WindowBase(QWidget *parent = 0);
    //Destructor
    ~WindowBase();

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


private:
    //Form - UI
};

#endif // WINDOWBASE_H
