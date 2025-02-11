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
    m_ConversionLastAddFilePath(Default::conversionLastAddFilePath),
    m_ConversionLastAddFolderPath(Default::conversionLastAddFolderPath),
    m_ConversionOutPath(Default::conversionOutPath),
    m_ConversionOutFormat(Default::conversionOutFormat),
    // Compression
    m_CompressionLastAddFilePath(Default::compressionLastAddFilePath),
    m_CompressionLastAddFolderPath(Default::compressionLastAddFolderPath),
    m_CompressionOutPath(Default::compressionOutPath),
    m_CompressionOutFormat(Default::compressionOutFormat) {
}

void Settings::load() {
    m_Settings.beginGroup("Conversion");
    m_ConversionOutPath = m_Settings.value(QStringLiteral("ConversionOutPath"), Default::conversionOutPath).toString();
    m_ConversionOutFormat = m_Settings.value(QStringLiteral("ConversionOutFormat"), Default::conversionOutFormat).toString();
    m_Settings.endGroup();
}

// Conversion
QString Settings::conversionLastAddFilePath() const {
    return m_ConversionLastAddFilePath;
}

void Settings::setConversionLastAddFilePath(const QString &path) {
    m_ConversionLastAddFilePath = path;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionLastAddFilePath"), m_ConversionLastAddFilePath);
    m_Settings.endGroup();
}

QString Settings::conversionLastAddFolderPath() const {
    return m_ConversionLastAddFolderPath;
}

void Settings::setConversionLastAddFolderPath(const QString &path) {
    m_ConversionLastAddFolderPath = path;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionLastAddFolderPath"), m_ConversionLastAddFolderPath);
    m_Settings.endGroup();
}

QString Settings::conversionOutPath() const {
    return m_ConversionOutPath;
}

void Settings::setConversionOutPath(const QString &path) {
    m_ConversionOutPath = path;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionOutPath"), m_ConversionOutPath);
    m_Settings.endGroup();
}

QString Settings::conversionOutFormat() const {
    return m_ConversionOutFormat;
}

void Settings::setConversionOutFormat(const QString &format) {
    m_ConversionOutFormat = format;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionOutFormat"), m_ConversionOutFormat);
    m_Settings.endGroup();
}

// Compression
QString Settings::compressionLastAddFilePath() const {
    return m_CompressionLastAddFilePath;
}

void Settings::setCompressionLastAddFilePath(const QString &path) {
    m_CompressionLastAddFilePath = path;
    m_Settings.beginGroup("Compression");
    m_Settings.setValue(QStringLiteral("CompressionLastAddFilePath"), m_CompressionLastAddFilePath);
    m_Settings.endGroup();
}

QString Settings::compressionLastAddFolderPath() const {
    return m_CompressionLastAddFolderPath;
}

void Settings::setCompressionLastAddFolderPath(const QString &path) {
    m_CompressionLastAddFolderPath = path;
    m_Settings.beginGroup("Compression");
    m_Settings.setValue(QStringLiteral("CompressionLastAddFolderPath"), m_CompressionLastAddFolderPath);
    m_Settings.endGroup();
}

QString Settings::compressionOutPath() const {
    return m_CompressionOutPath;
}

void Settings::setCompressionOutPath(const QString &path) {
    m_CompressionOutPath = path;
    m_Settings.beginGroup("Compression");
    m_Settings.setValue(QStringLiteral("CompressionOutPath"), m_CompressionOutPath);
    m_Settings.endGroup();
}

QString Settings::compressionOutFormat() const {
    return m_CompressionOutFormat;
}

void Settings::setCompressionOutFormat(const QString &format) {
    m_CompressionOutFormat = format;
    m_Settings.beginGroup("Compression");
    m_Settings.setValue(QStringLiteral("CompressionOutFormat"), m_CompressionOutFormat);
    m_Settings.endGroup();
}