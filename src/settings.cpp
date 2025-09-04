#include "inc/settings.h"
#include <QApplication>

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
    m_strCompressionOutFormat(Default::compressionOutFormat),
    m_nCompressQuality(Default::compressionQuality),
    m_strGifMkLastAddFilePath(Default::gifMkLastAddFilePath),
    m_strGifMkLastAddFolderPath(Default::gifMkLastAddFolderPath),
    m_nGifMkWidth(Default::gifMkWidth),
    m_nGifMkHeight(Default::gifMkHeight),
    m_nGifMkQuality(Default::gifMkQuality),
    m_nGifMkFps(Default::gifMkFps),
    m_bGifMkRepeat(Default::gifMkRepeat),
    m_strGifMkOutPath(Default::gifMkOutPath),
    // BgRm
    m_strBgRmLastAddFilePath(Default::backgroundRemoverLastAddFilePath),
    m_strBgRmLastAddFolderPath(Default::backgroundRemoverLastAddFolderPath),
    m_strBgRmOutPath(Default::backgroundRemoverOutPath),
    // Enhance
    m_strEnhanceOutPath(Default::enhanceOutPath),
    // Enhance
    m_strEraseOutPath(Default::eraseOutPath),
    // crop
    m_strCropOutPath(Default::cropOutPath)
{
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

// GifMk
QString Settings::gifMkLastAddFilePath() const {
    return m_strGifMkLastAddFilePath;
}

void Settings::setGifMkLastAddFilePath(const QString &path) {
    m_strGifMkLastAddFilePath = path;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("GifMkLastAddFilePath"), m_strGifMkLastAddFilePath);
    m_Settings.endGroup();
}

QString Settings::gifMkLastAddFolderPath() const {
    return m_strGifMkLastAddFolderPath;
}

void Settings::setGifMkLastAddFolderPath(const QString &path) {
    m_strGifMkLastAddFolderPath = path;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("GifMkLastAddFolderPath"), m_strGifMkLastAddFolderPath);
    m_Settings.endGroup();
}

int Settings::gifMkWidth() const {
    return m_nGifMkWidth;
}

void Settings::setGifMkWidth(const int width) {
    m_nGifMkWidth = width;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("GifMkWidth"), m_nGifMkWidth);
    m_Settings.endGroup();
}

int Settings::gifMkHeight() const {
    return m_nGifMkHeight;
}

void Settings::setGifMkHeight(const int height) {
    m_nGifMkHeight = height;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("GifMkHeight"), m_nGifMkHeight);
    m_Settings.endGroup();
}

int Settings::gifMkQuality() const {
    return m_nGifMkQuality;
}

void Settings::setGifMkQuality(const int quality) {
    m_nGifMkQuality = quality;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("GifMkQuality"), m_nGifMkQuality);
    m_Settings.endGroup();
}

int Settings::gifMkFps() const {
    return m_nGifMkFps;
}

void Settings::setGifMkFps(const int fps) {
    m_nGifMkFps = fps;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("GifMkFps"), m_nGifMkFps);
    m_Settings.endGroup();
}

bool Settings::gifMkRepeat() const {
    return m_bGifMkRepeat;
}

void Settings::setGifMkRepeat(bool repeat) {
    m_bGifMkRepeat = repeat;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("GifMkRepeat"), m_bGifMkRepeat);
    m_Settings.endGroup();
}

QString Settings::gifMkOutPath() const {
    return m_strGifMkOutPath;
}

void Settings::setGifMkOutPath(const QString &path) {
    m_strGifMkOutPath = path;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("GifMkOutPath"), m_strGifMkOutPath);
    m_Settings.endGroup();
}

// BgRm
QString Settings::bgRmLastAddFilePath() const {
    return m_strBgRmLastAddFilePath;
}

void Settings::setBgRmLastAddFilePath(const QString &path) {
    m_strBgRmLastAddFilePath = path;
    m_Settings.beginGroup("BgRm");
    m_Settings.setValue(QStringLiteral("BgRmLastAddFilePath"), m_strBgRmLastAddFilePath);
    m_Settings.endGroup();
}

QString Settings::bgRmLastAddFolderPath() const {
    return m_strBgRmLastAddFolderPath;
}

void Settings::setBgRmLastAddFolderPath(const QString &path) {
    m_strBgRmLastAddFolderPath = path;
    m_Settings.beginGroup("BgRm");
    m_Settings.setValue(QStringLiteral("BgRmLastAddFolderPath"), m_strBgRmLastAddFolderPath);
    m_Settings.endGroup();
}

QString Settings::bgRmOutPath() const {
    return m_strBgRmOutPath;
}

void Settings::setBgRmOutPath(const QString &path) {
    m_strBgRmOutPath = path;
    m_Settings.beginGroup("BgRm");
    m_Settings.setValue(QStringLiteral("BgRmOutPath"), m_strBgRmOutPath);
    m_Settings.endGroup();
}

// Enhance
QString Settings::enhanceOutPath() const {
    return m_strEnhanceOutPath;
}

void Settings::setEnhanceOutPath(const QString &path) {
    m_strEnhanceOutPath = path;
    m_Settings.beginGroup("Enhance");
    m_Settings.setValue(QStringLiteral("EnhanceOutPath"), m_strEnhanceOutPath);
    m_Settings.endGroup();
}

// erase
QString Settings::eraseOutPath() const {
    return m_strEraseOutPath;
}

void Settings::setEraseOutPath(const QString &path) {
    m_strEraseOutPath = path;
    m_Settings.beginGroup("Erase");
    m_Settings.setValue(QStringLiteral("EraseOutPath"), m_strEraseOutPath);
    m_Settings.endGroup();
}

// crop
QString Settings::cropOutPath() const {
    return m_strCropOutPath;
}

void Settings::setCropOutPath(const QString &path) {
    m_strCropOutPath = path;
    m_Settings.beginGroup("Crop");
    m_Settings.setValue(QStringLiteral("CropOutPath"), m_strCropOutPath);
    m_Settings.endGroup();
}