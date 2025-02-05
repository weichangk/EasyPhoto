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
// Convert
static QString conversionOutPath = defOutPath("Conversion");
static QString conversionOutFormat = "png";
static QString conversionLastAddFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
static QString conversionLastAddFolderPath = QDir::homePath();
} // namespace Default

Settings::Settings() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()),
    m_ConversionLastAddFilePath(Default::conversionLastAddFilePath),
    m_ConversionLastAddFolderPath(Default::conversionLastAddFolderPath),
    m_ConversionOutPath(Default::conversionOutPath),
    m_ConversionOutFormat(Default::conversionOutFormat) {
}

void Settings::load() {
    m_Settings.beginGroup("Conversion");
    m_ConversionOutPath = m_Settings.value(QStringLiteral("ConversionOutPath"), Default::conversionOutPath).toString();
    m_ConversionOutFormat = m_Settings.value(QStringLiteral("ConversionOutFormat"), Default::conversionOutFormat).toString();
    m_Settings.endGroup();
}

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