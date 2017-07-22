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

    static std::string QStringToString(QString str);

    static QString StringToQString(std::string str);

    static QString StringToQString(const char * str);

    static bool StringToBoolean(std::string str);

    static bool QStringToBoolean(QString str);

    static std::string ParseCommand(QString str, QString delim, std::string &command);

    static std::vector<std::pair<std::string, std::string>> ParseArguments(QString str, QString argDelim, QString valueDelim);

    static void DumpArgumentsToConsole(std::vector<std::pair<std::string, std::string>> arguments);
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
