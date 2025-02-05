#pragma once
#include "core/singlton.h"

#include <QSettings>
#include <QDir>
#include <QStandardPaths>

using namespace qtmaterialcore;

class Settings: public Singlton<Settings> {
public:
    Settings();
    void load();

    // Convert
    QString conversionLastAddFilePath() const;
    void setConversionLastAddFilePath(const QString &path);
    QString conversionLastAddFolderPath() const;
    void setConversionLastAddFolderPath(const QString &path);
    QString conversionOutPath() const;
    void setConversionOutPath(const QString &path);
    QString conversionOutFormat() const;
    void setConversionOutFormat(const QString &format);


private:
    QSettings m_Settings;

    // Convert
    QString m_ConversionLastAddFilePath;
    QString m_ConversionLastAddFolderPath;
    QString m_ConversionOutPath;
    QString m_ConversionOutFormat;
};

#define SETTINGS Settings::getInstance()
