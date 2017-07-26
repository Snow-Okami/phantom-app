#include "main/utilities/include/settings.h"

//Initialize Static Vars
QString Settings::m_sSettingsFile = 0;
//----
QString Settings::savedAccountName = 0;
QString Settings::desysiaGameLocationDir = 0;

Settings::Settings()
{
    InitializeSettings();
}

void Settings::InitializeSettings()
{
    Settings::m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/settings.ini";
    LoadSettings();
}

void Settings::LoadSettings()
{
    QSettings settings(Settings::m_sSettingsFile, QSettings::IniFormat);
    Settings::savedAccountName = settings.value("savedAccountName", "").toString();
    Settings::desysiaGameLocationDir = settings.value("desysiaGameLocationDir", "").toString();
}

void Settings::SaveSettings()
{
    QSettings settings(Settings::m_sSettingsFile, QSettings::IniFormat);
    settings.setValue("savedAccountName", Settings::savedAccountName);
    settings.setValue("desysiaGameLocationDir", Settings::desysiaGameLocationDir);
}
