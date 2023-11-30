#include "inc/settings.h"
#include <QApplication>
#include <QSettings>

Settings::Settings()
    : m_AutoStart(Default::autoStart)
{
}

void Settings::load()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
                       QApplication::applicationDisplayName());

    settings.beginGroup("General");
    m_AutoStart = settings.value(QStringLiteral("AutoStart"), Default::autoStart).toBool();
    settings.endGroup();
}

void Settings::save()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
                       QApplication::applicationDisplayName());

    settings.beginGroup("General");
    settings.setValue(QStringLiteral("AutoStart"), m_AutoStart);
    settings.endGroup();
}
