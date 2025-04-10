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

    // BackgroungRemover
    QString backgroungRemoverLastAddFilePath() const;
    void setBackgroungRemoverLastAddFilePath(const QString &path);
    QString backgroungRemoverLastAddFolderPath() const;
    void setBackgroungRemoverLastAddFolderPath(const QString &path);
    QString backgroungRemoverOutPath() const;
    void setBackgroungRemoverOutPath(const QString &path);

    // Enhance
    QString enhanceOutPath() const;
    void setEnhanceOutPath(const QString &path);

    // erase
    QString eraseOutPath() const;
    void setEraseOutPath(const QString &path);

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

    // BackgroungRemover
    QString m_strBackgroungRemoverLastAddFilePath;
    QString m_strBackgroungRemoverLastAddFolderPath;
    QString m_strBackgroungRemoverOutPath;

    // Enhance
    QString m_strEnhanceOutPath;

    // erase
    QString m_strEraseOutPath;
};

#define SETTINGS Settings::getInstance()
