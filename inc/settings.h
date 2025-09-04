#pragma once
#include "core/singlton.h"

#include <QSettings>
#include <QDir>
#include <QStandardPaths>

using namespace QtmCore;

static QString defOutPath(const QString &folderName) {
    QString fullPath = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    QString picturesFolder = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (!picturesFolder.isEmpty()) {
        QDir additionalFolder(picturesFolder);
        additionalFolder.mkpath(folderName);
        fullPath = additionalFolder.filePath(folderName);
    }
    return fullPath;
}

namespace Default {
// Conversion
static QString conversionOutPath = defOutPath("Conversion");
static QString conversionOutFormat = "png";
static QString conversionLastAddFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
static QString conversionLastAddFolderPath = QDir::homePath();

// Compression
static QString compressionOutPath = defOutPath("Compression");
static QString compressionOutFormat = "sameassource";
static QString compressionLastAddFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
static QString compressionLastAddFolderPath = QDir::homePath();
static int compressionQuality = 60;

// GifGeneration
static QString gifGenerationOutPath = defOutPath("GifGeneration");
static QString gifGenerationLastAddFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
static QString gifGenerationLastAddFolderPath = QDir::homePath();
static int gifGenerationWidth = 640;
static int gifGenerationHeight = 640;
static int gifGenerationQuality = 100;
static int gifGenerationFps = 25;
static bool gifGenerationRepeat = true;

// BgRm
static QString backgroundRemoverOutPath = defOutPath("BackgroundRemover");
static QString backgroundRemoverLastAddFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
static QString backgroundRemoverLastAddFolderPath = QDir::homePath();

// Enhance
static QString enhanceOutPath = defOutPath("Enhance");

// erase
static QString eraseOutPath = defOutPath("Erase");

// crop
static QString cropOutPath = defOutPath("Crop");

} // namespace Default

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

    // GifGeneration
    QString gifGenerationLastAddFilePath() const;
    void setGifGenerationLastAddFilePath(const QString &path);
    QString gifGenerationLastAddFolderPath() const;
    void setGifGenerationLastAddFolderPath(const QString &path);
    int gifGenerationWidth() const;
    void setGifGenerationWidth(const int width);
    int gifGenerationHeight() const;
    void setGifGenerationHeight(const int height);
    int gifGenerationQuality() const;
    void setGifGenerationQuality(const int quality);
    int gifGenerationFps() const;
    void setGifGenerationFps(const int fps);
    bool gifGenerationRepeat() const;
    void setGifGenerationRepeat(bool repeat);
    QString gifGenerationOutPath() const;
    void setGifGenerationOutPath(const QString &path);

    // BgRm
    QString bgRmLastAddFilePath() const;
    void setBgRmLastAddFilePath(const QString &path);
    QString bgRmLastAddFolderPath() const;
    void setBgRmLastAddFolderPath(const QString &path);
    QString bgRmOutPath() const;
    void setBgRmOutPath(const QString &path);

    // Enhance
    QString enhanceOutPath() const;
    void setEnhanceOutPath(const QString &path);

    // erase
    QString eraseOutPath() const;
    void setEraseOutPath(const QString &path);

    // crop
    QString cropOutPath() const;
    void setCropOutPath(const QString &path);

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

    // GifGeneration
    QString m_strGifGenerationLastAddFilePath;
    QString m_strGifGenerationLastAddFolderPath;
    int m_nGifGenerationWidth;
    int m_nGifGenerationHeight;
    int m_nGifGenerationQuality;
    int m_nGifGenerationFps;
    bool m_bGifGenerationRepeat;
    QString m_strGifGenerationOutPath;

    // BgRm
    QString m_strBgRmLastAddFilePath;
    QString m_strBgRmLastAddFolderPath;
    QString m_strBgRmOutPath;

    // Enhance
    QString m_strEnhanceOutPath;

    // erase
    QString m_strEraseOutPath;

    // crop
    QString m_strCropOutPath;
};

#define SETTINGS Settings::getInstance()
