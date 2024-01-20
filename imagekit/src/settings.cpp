/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:50
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-20 00:07:15
 */

#include "inc/settings.h"
#include <QApplication>
#include <QSettings>

Settings::Settings() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()),
    m_AutoStart(Default::autoStart),
    m_ConversionOutPath(Default::conversionOutPath),
    m_ConversionOutFormat(Default::conversionOutFormat) {
}

void Settings::load() {
    m_Settings.beginGroup("General");
    m_AutoStart = m_Settings.value(QStringLiteral("AutoStart"), Default::autoStart).toBool();
    m_Settings.endGroup();

    m_Settings.beginGroup("Conversion");
    m_ConversionOutPath = m_Settings.value(QStringLiteral("ConversionOutPath"), Default::conversionOutPath).toString();
    m_Settings.endGroup();
}

bool Settings::autoStart() const {
    return m_AutoStart;
}

void Settings::setAutoStart(const bool autoStart) {
    m_AutoStart = autoStart;
    m_Settings.beginGroup("General");
    m_Settings.setValue(QStringLiteral("AutoStart"), m_AutoStart);
    m_Settings.endGroup();
}

QString Settings::conversionOutPath() const {
    return m_ConversionOutPath;
}

void Settings::setConversionOutPath(const QString path) {
    m_ConversionOutPath = path;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionOutPath"), m_ConversionOutPath);
    m_Settings.endGroup();
}

QString Settings::conversionOutFormat() const {
    return m_ConversionOutFormat;
}

void Settings::setConversionOutFormat(const QString format) {
    m_ConversionOutFormat = format;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionOutFormat"), m_ConversionOutFormat);
    m_Settings.endGroup();
}
