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

    // Conversion
    QString conversionLastAddFilePath() const;
    void setConversionLastAddFilePath(const QString &path);
    QString conversionLastAddFolderPath() const;
    void setConversionLastAddFolderPath(const QString &path);
    QString conversionOutPath() const;
    void setConversionOutPath(const QString &path);
    QString conversionOutFormat() const;
    void setConversionOutFormat(const QString &format);

    // Compression
    QString compressionLastAddFilePath() const;
    void setCompressionLastAddFilePath(const QString &path);
    QString compressionLastAddFolderPath() const;
    void setCompressionLastAddFolderPath(const QString &path);
    QString compressionOutPath() const;
    void setCompressionOutPath(const QString &path);
    QString compressionOutFormat() const;
    void setCompressionOutFormat(const QString &format);

private:
    QSettings m_Settings;

    // Conversion
    QString m_ConversionLastAddFilePath;
    QString m_ConversionLastAddFolderPath;
    QString m_ConversionOutPath;
    QString m_ConversionOutFormat;

    // Compression
    QString m_CompressionLastAddFilePath;
    QString m_CompressionLastAddFolderPath;
    QString m_CompressionOutPath;
    QString m_CompressionOutFormat;
};

#define SETTINGS Settings::getInstance()
