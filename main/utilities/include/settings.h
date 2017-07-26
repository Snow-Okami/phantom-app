#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QCoreApplication>
#include <QSettings>
#include <QApplication>

class Settings
{
public:
    Settings();

    static void InitializeSettings();
    static void LoadSettings();
    static void SaveSettings();

    static QString m_sSettingsFile;

public:
    static QString savedAccountName;
    static QString desysiaGameLocationDir;
};

#endif // SETTINGS_H
