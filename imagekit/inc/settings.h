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
        QString folderName = "conversion";
        QDir additionalFolder(picturesFolder);
        additionalFolder.mkpath(folderName);
        fullPath = additionalFolder.filePath(folderName);
    }
    return fullPath;
}

namespace Default {
static constexpr bool autoStart = false;
static QString conversionOutPath = defConversionOutPath();
static QString conversionOutFormat = "png";
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
    QString conversionOutPath() const;
    void setConversionOutPath(const QString path);
    QString conversionOutFormat() const;
    void setConversionOutFormat(const QString format);

private:
    QSettings m_Settings;
    bool m_AutoStart;
    QString m_ConversionOutPath;
    QString m_ConversionOutFormat;
};

#define SETTINGS Settings::getInstance()
