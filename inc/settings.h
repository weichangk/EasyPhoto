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
    int compressQuality() const;
    void setCompressQuality(const int quality);
private:
    QSettings m_Settings;

    // Conversion
    QString m_strConversionLastAddFilePath;
    QString m_strConversionLastAddFolderPath;
    QString m_strConversionOutPath;
    QString m_strConversionOutFormat;

    // Compression
    QString m_strCompressionLastAddFilePath;
    QString m_strCompressionLastAddFolderPath;
    QString m_strCompressionOutPath;
    QString m_strCompressionOutFormat;
    int m_nCompressQuality;
};

#define SETTINGS Settings::getInstance()
