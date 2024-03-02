/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:19
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-20 00:03:47
 */

#pragma once
#include "../acore/inc/asinglton.h"
#include <QSettings>
#include <QDir>
#include <QStandardPaths>

static QString defConversionOutPath() {
    QString fullPath = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    QString picturesFolder = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (!picturesFolder.isEmpty()) {
        QString folderName = "convert";
        QDir additionalFolder(picturesFolder);
        additionalFolder.mkpath(folderName);
        fullPath = additionalFolder.filePath(folderName);
    }
    return fullPath;
}

static QString defCompressOutPath() {
    QString fullPath = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    QString picturesFolder = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (!picturesFolder.isEmpty()) {
        QString folderName = "compress";
        QDir additionalFolder(picturesFolder);
        additionalFolder.mkpath(folderName);
        fullPath = additionalFolder.filePath(folderName);
    }
    return fullPath;
}

namespace Default {
// Common
static constexpr bool autoStart = false;

// Convert
static QString conversionOutPath = defConversionOutPath();
static QString conversionOutFormat = "png";

// Compress
static QString compressOutPath = defCompressOutPath();
static QString compressOutFormat = "sameassource";
static int compressQuality = 60;
}

namespace Limits {
static constexpr int zoomMax = 5;
}

class Settings: public ASinglton<Settings> {
public:
    Settings();
    void load();
    bool autoStart() const;
    void setAutoStart(const bool autoStart);

    // Convert
    QString conversionOutPath() const;
    void setConversionOutPath(const QString path);
    QString conversionOutFormat() const;
    void setConversionOutFormat(const QString format);

    // Compress
    QString compressOutPath() const;
    void setCompressOutPath(const QString path);
    QString compressOutFormat() const;
    void setCompressOutFormat(const QString format);
    int compressQuality() const;
    void setCompressQuality(const int quality);

private:
    QSettings m_Settings;
    // Common
    bool m_AutoStart;

    // Convert
    QString m_ConversionOutPath;
    QString m_ConversionOutFormat;

    // Compress
    QString m_CompressOutPath;
    QString m_CompressOutFormat;
    int m_CompressQuality;
};

#define SETTINGS Settings::getInstance()
