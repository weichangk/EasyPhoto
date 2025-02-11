#include "inc/settings.h"
#include <QApplication>

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
} // namespace Default

Settings::Settings() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()),
    // Conversion
    m_strConversionLastAddFilePath(Default::conversionLastAddFilePath),
    m_strConversionLastAddFolderPath(Default::conversionLastAddFolderPath),
    m_strConversionOutPath(Default::conversionOutPath),
    m_strConversionOutFormat(Default::conversionOutFormat),
    // Compression
    m_strCompressionLastAddFilePath(Default::compressionLastAddFilePath),
    m_strCompressionLastAddFolderPath(Default::compressionLastAddFolderPath),
    m_strCompressionOutPath(Default::compressionOutPath),
    m_strCompressionOutFormat(Default::compressionOutFormat) {
}

void Settings::load() {
    m_Settings.beginGroup("Conversion");
    m_strConversionOutPath = m_Settings.value(QStringLiteral("ConversionOutPath"), Default::conversionOutPath).toString();
    m_strConversionOutFormat = m_Settings.value(QStringLiteral("ConversionOutFormat"), Default::conversionOutFormat).toString();
    m_Settings.endGroup();
}

// Conversion
QString Settings::conversionLastAddFilePath() const {
    return m_strConversionLastAddFilePath;
}

void Settings::setConversionLastAddFilePath(const QString &path) {
    m_strConversionLastAddFilePath = path;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionLastAddFilePath"), m_strConversionLastAddFilePath);
    m_Settings.endGroup();
}

QString Settings::conversionLastAddFolderPath() const {
    return m_strConversionLastAddFolderPath;
}

void Settings::setConversionLastAddFolderPath(const QString &path) {
    m_strConversionLastAddFolderPath = path;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionLastAddFolderPath"), m_strConversionLastAddFolderPath);
    m_Settings.endGroup();
}

QString Settings::conversionOutPath() const {
    return m_strConversionOutPath;
}

void Settings::setConversionOutPath(const QString &path) {
    m_strConversionOutPath = path;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionOutPath"), m_strConversionOutPath);
    m_Settings.endGroup();
}

QString Settings::conversionOutFormat() const {
    return m_strConversionOutFormat;
}

void Settings::setConversionOutFormat(const QString &format) {
    m_strConversionOutFormat = format;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionOutFormat"), m_strConversionOutFormat);
    m_Settings.endGroup();
}

// Compression
QString Settings::compressionLastAddFilePath() const {
    return m_strCompressionLastAddFilePath;
}

void Settings::setCompressionLastAddFilePath(const QString &path) {
    m_strCompressionLastAddFilePath = path;
    m_Settings.beginGroup("Compression");
    m_Settings.setValue(QStringLiteral("CompressionLastAddFilePath"), m_strCompressionLastAddFilePath);
    m_Settings.endGroup();
}

QString Settings::compressionLastAddFolderPath() const {
    return m_strCompressionLastAddFolderPath;
}

void Settings::setCompressionLastAddFolderPath(const QString &path) {
    m_strCompressionLastAddFolderPath = path;
    m_Settings.beginGroup("Compression");
    m_Settings.setValue(QStringLiteral("CompressionLastAddFolderPath"), m_strCompressionLastAddFolderPath);
    m_Settings.endGroup();
}

QString Settings::compressionOutPath() const {
    return m_strCompressionOutPath;
}

void Settings::setCompressionOutPath(const QString &path) {
    m_strCompressionOutPath = path;
    m_Settings.beginGroup("Compression");
    m_Settings.setValue(QStringLiteral("CompressionOutPath"), m_strCompressionOutPath);
    m_Settings.endGroup();
}

QString Settings::compressionOutFormat() const {
    return m_strCompressionOutFormat;
}

void Settings::setCompressionOutFormat(const QString &format) {
    m_strCompressionOutFormat = format;
    m_Settings.beginGroup("Compression");
    m_Settings.setValue(QStringLiteral("CompressionOutFormat"), m_strCompressionOutFormat);
    m_Settings.endGroup();
}

int Settings::compressQuality() const {
    return m_nCompressQuality;
}

void Settings::setCompressQuality(const int quality) {
    m_nCompressQuality = quality;
    m_Settings.beginGroup("Compression");
    m_Settings.setValue(QStringLiteral("CompressQuality"), m_nCompressQuality);
    m_Settings.endGroup();
}