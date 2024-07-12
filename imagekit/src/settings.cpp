/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:50
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-20 00:07:15
 */

#include "inc/settings.h"
#include "inc/models.h"
#include <QApplication>
#include <QSettings>

static QString defOutPath(const QString &folderName) {
    QString fullPath = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    QString picturesFolder = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (!picturesFolder.isEmpty()) {
        // QString folderName = "convert";
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
static QString conversionOutPath = defOutPath("convert");
static QString conversionOutFormat = "png";

// Compress
static QString compressOutPath = defOutPath("compress");
static QString compressOutFormat = "sameassource";
static int compressQuality = 60;
}

namespace Limits {
static constexpr int zoomMax = 5;
}

namespace image2gif {
static const QString kGifKey = "gif";
static const QString kGifFpsKey = "gif/gif_fps";
static const QString kGifQualityKey = "gif/gif_quality";
static const QString kGifResolutionKey = "gif/gif_resolution";
static const QString kGifWidthKey = "gif/gif_width";
static const QString kGifHeightKey = "gif/gif_height";
static const QString kGifRepeatKey = "gif/gif_repeat";
static const QString kGifOutpathKey = "gif/gif_outpath";

static const int kGifFpsDefValue = 3;
static const int kGifQualityDefValue = 1;
static const int kGifResolutionDefValue = 1;
static const int kGifWidthDefValue = 640;
static const int kGifHeightDefValue = 480;
static const bool kGifRepeatDefValue = true;
static const QString kGifOutpathDefValue = defOutPath("gif");
} // namespace image2gif

Settings::Settings() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()),
    m_AutoStart(Default::autoStart),
    m_ConversionOutPath(Default::conversionOutPath),
    m_ConversionOutFormat(Default::conversionOutFormat),
    m_CompressOutFormat(Default::compressOutFormat),
    m_CompressOutPath(Default::compressOutPath),
    m_CompressQuality(Default::compressQuality),
    gif_fps_(image2gif::kGifFpsDefValue),
    gif_quality_(image2gif::kGifQualityDefValue),
    gif_resolution_(image2gif::kGifResolutionDefValue),
    gif_width_(image2gif::kGifWidthDefValue),
    gif_height_(image2gif::kGifHeightDefValue),
    gif_repeat_(image2gif::kGifRepeatDefValue),
    gif_outpath_(image2gif::kGifOutpathDefValue) {
}

void Settings::load() {
    m_Settings.beginGroup("General");
    m_AutoStart = m_Settings.value(QStringLiteral("AutoStart"), Default::autoStart).toBool();
    m_Settings.endGroup();

    m_Settings.beginGroup("Conversion");
    m_ConversionOutPath = m_Settings.value(QStringLiteral("ConversionOutPath"), Default::conversionOutPath).toString();
    m_ConversionOutFormat = m_Settings.value(QStringLiteral("ConversionOutFormat"), Default::conversionOutFormat).toString();
    m_Settings.endGroup();

    gif_fps_ = m_Settings.value(image2gif::kGifFpsKey, image2gif::kGifFpsDefValue).toInt();
    gif_quality_ = m_Settings.value(image2gif::kGifQualityKey, image2gif::kGifQualityDefValue).toInt();
    gif_resolution_ = m_Settings.value(image2gif::kGifResolutionKey, image2gif::kGifResolutionDefValue).toInt();
    gif_width_ = m_Settings.value(image2gif::kGifWidthKey, image2gif::kGifWidthDefValue).toInt();
    gif_height_ = m_Settings.value(image2gif::kGifHeightKey, image2gif::kGifHeightDefValue).toInt();
    gif_repeat_ = m_Settings.value(image2gif::kGifRepeatKey, image2gif::kGifRepeatDefValue).toBool();
    gif_outpath_ = m_Settings.value(image2gif::kGifOutpathKey, image2gif::kGifOutpathDefValue).toString();
}

bool Settings::autoStart() const {
    return m_AutoStart;
}

void Settings::setAutoStart(const bool autoStart) {
    m_AutoStart = autoStart;
    m_Settings.beginGroup("General");
    m_Settings.setValue(QStringLiteral("AutoStart"), m_AutoStart);
    m_Settings.endGroup();
}

QString Settings::conversionOutPath() const {
    return m_ConversionOutPath;
}

void Settings::setConversionOutPath(const QString path) {
    m_ConversionOutPath = path;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionOutPath"), m_ConversionOutPath);
    m_Settings.endGroup();
}

QString Settings::conversionOutFormat() const {
    return m_ConversionOutFormat;
}

void Settings::setConversionOutFormat(const QString format) {
    m_ConversionOutFormat = format;
    m_Settings.beginGroup("Conversion");
    m_Settings.setValue(QStringLiteral("ConversionOutFormat"), m_ConversionOutFormat);
    m_Settings.endGroup();
}

QString Settings::compressOutPath() const {
    return m_CompressOutPath;
}

void Settings::setCompressOutPath(const QString path) {
    m_CompressOutPath = path;
}

QString Settings::compressOutFormat() const {
    return m_CompressOutFormat;
}

void Settings::setCompressOutFormat(const QString format) {
    m_CompressOutFormat = format;
}

int Settings::compressQuality() const {
    return m_CompressQuality;
}

void Settings::setCompressQuality(const int quality) {
    m_CompressQuality = quality;
}

int Settings::gifFps() const {
    return gif_fps_;
}

void Settings::setGifFps(const int fps) {
    gif_fps_ = fps;
    m_Settings.setValue(image2gif::kGifFpsKey, gif_fps_);
}

int Settings::gifQuality() const {
    return gif_quality_;
}

void Settings::setGifQuality(const int quality) {
    gif_quality_ = quality;
    m_Settings.setValue(image2gif::kGifQualityKey, gif_quality_);
}

int Settings::gifResolution() const {
    return gif_resolution_;
}

void Settings::setGifResolution(const int resolution) {
    gif_resolution_ = resolution;
    m_Settings.setValue(image2gif::kGifResolutionKey, gif_resolution_);
}

int Settings::gifWidth() const {
    if(gif_resolution_ == ImageResolution::Custom)
        return gif_width_;
    else
        return ImageResolutionSizeMap[(ImageResolution)gif_resolution_].width();
}

void Settings::setGifWidth(const int width) {
    gif_width_ = width;
    m_Settings.setValue(image2gif::kGifWidthKey, gif_width_);
}

int Settings::gifHeight() const {
    if(gif_resolution_ == ImageResolution::Custom)
        return gif_height_;
    else
        return ImageResolutionSizeMap[(ImageResolution)gif_resolution_].height();
}

void Settings::setGifHeight(const int height) {
    gif_height_ = height;
    m_Settings.setValue(image2gif::kGifHeightKey, gif_height_);
}

bool Settings::gifRepeat() const {
    return gif_repeat_;
}

void Settings::setGifRepeat(const bool repeat) {
    gif_repeat_ = repeat;
    m_Settings.setValue(image2gif::kGifRepeatKey, gif_repeat_);
}

QString Settings::gifOutpath() const {
    return gif_outpath_;
}

void Settings::setGifOutpath(const QString path) {
    gif_outpath_ = path;
    m_Settings.setValue(image2gif::kGifOutpathKey, gif_outpath_);
}