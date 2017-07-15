#ifndef UTILITIES_H
#define UTILITIES_H

#include <QWidget>
#include <QPushButton>
#include <QToolBar>

#include <QApplication>
#include <QHBoxLayout>
#include <QStyle>
#include <QLabel>
#include <QTextStream>

#include <ostream>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::osstream

class Utilities
{
public:    

    static QString Input();

    static void SetEnabledWidgetsInLayout(QLayout *layout, bool enabled);

    static bool IsChildWidgetOfAnyLayout(QLayout *layout, QWidget *widget);

    static const char * const BoolToString(bool value);
};

template<typename T>
class Logger
{
public:
    static void Output(T value, bool endLine = true);
};

template<typename T>
void Logger<T>::Output(T value, bool endLine)
{
    QTextStream cout(stdout);

    T newType = qobject_cast<T>(value);

    if(endLine)
        cout << newType << endl;
    else
        cout << newType;
}

#endif // UTILITIES_H
