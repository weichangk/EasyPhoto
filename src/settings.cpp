#include "inc/settings.h"
#include <QApplication>

ConvSetting::ConvSetting() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()) {
}

void ConvSetting::load() {
    m_Settings.beginGroup("Conv");
    m_OutPath = m_Settings.value(QStringLiteral("OutPath"), Default::Conv::outPath).toString();
    m_OutFmt = m_Settings.value(QStringLiteral("OutFmt"), Default::Conv::outFormat).toString();
    m_LastAddFilePath = m_Settings.value(QStringLiteral("LastAddFilePath"), Default::Conv::lastAddFilePath).toString();
    m_LastAddFolderPath = m_Settings.value(QStringLiteral("LastAddFolderPath"), Default::Conv::lastAddFolderPath).toString();
    m_Settings.endGroup();
}

QString ConvSetting::getOutPath() const {
    return m_OutPath;
}

void ConvSetting::setOutPath(const QString &path) {
    m_OutPath = path;
    m_Settings.beginGroup("Conv");
    m_Settings.setValue(QStringLiteral("OutPath"), m_OutPath);
    m_Settings.endGroup();
}

QString ConvSetting::getOutFmt() const {
    return m_OutFmt;
}

void ConvSetting::setOutFmt(const QString &fmt) {
    m_OutFmt = fmt;
    m_Settings.beginGroup("Conv");
    m_Settings.setValue(QStringLiteral("OutFmt"), m_OutFmt);
    m_Settings.endGroup();
}

QString ConvSetting::getLastAddFilePath() const {
    return m_LastAddFilePath;
}

void ConvSetting::setLastAddFilePath(const QString &path) {
    m_LastAddFilePath = path;
    m_Settings.beginGroup("Conv");
    m_Settings.setValue(QStringLiteral("LastAddFilePath"), m_LastAddFilePath);
    m_Settings.endGroup();
}

QString ConvSetting::getLastAddFolderPath() const {
    return m_LastAddFolderPath;
}

void ConvSetting::setLastAddFolderPath(const QString &path) {
    m_LastAddFolderPath = path;
    m_Settings.beginGroup("Conv");
    m_Settings.setValue(QStringLiteral("LastAddFolderPath"), m_LastAddFolderPath);
    m_Settings.endGroup();
}

CompSetting::CompSetting() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()) {
}

void CompSetting::load() {
    m_Settings.beginGroup("Comp");
    m_OutPath = m_Settings.value(QStringLiteral("OutPath"), Default::Comp::outPath).toString();
    m_OutFmt = m_Settings.value(QStringLiteral("OutFmt"), Default::Comp::outFormat).toString();
    m_LastAddFilePath = m_Settings.value(QStringLiteral("LastAddFilePath"), Default::Comp::lastAddFilePath).toString();
    m_LastAddFolderPath = m_Settings.value(QStringLiteral("LastAddFolderPath"), Default::Comp::lastAddFolderPath).toString();
    m_Quality = m_Settings.value(QStringLiteral("Quality"), Default::Comp::quality).toInt();
    m_Settings.endGroup();
}

QString CompSetting::getOutPath() const {
    return m_OutPath;
}

void CompSetting::setOutPath(const QString &path) {
    m_OutPath = path;
    m_Settings.beginGroup("Comp");
    m_Settings.setValue(QStringLiteral("OutPath"), m_OutPath);
    m_Settings.endGroup();
}

QString CompSetting::getOutFmt() const {
    return m_OutFmt;
}

void CompSetting::setOutFmt(const QString &fmt) {
    m_OutFmt = fmt;
    m_Settings.beginGroup("Comp");
    m_Settings.setValue(QStringLiteral("OutFmt"), m_OutFmt);
    m_Settings.endGroup();
}

QString CompSetting::getLastAddFilePath() const {
    return m_LastAddFilePath;
}

void CompSetting::setLastAddFilePath(const QString &path) {
    m_LastAddFilePath = path;
    m_Settings.beginGroup("Comp");
    m_Settings.setValue(QStringLiteral("LastAddFilePath"), m_LastAddFilePath);
    m_Settings.endGroup();
}

QString CompSetting::getLastAddFolderPath() const {
    return m_LastAddFolderPath;
}

void CompSetting::setLastAddFolderPath(const QString &path) {
    m_LastAddFolderPath = path;
    m_Settings.beginGroup("Comp");
    m_Settings.setValue(QStringLiteral("LastAddFolderPath"), m_LastAddFolderPath);
    m_Settings.endGroup();
}

int CompSetting::getQuality() const {
    return m_Quality;
}

void CompSetting::setQuality(int q) {
    m_Quality = q;
    m_Settings.beginGroup("Comp");
    m_Settings.setValue(QStringLiteral("Quality"), m_Quality);
    m_Settings.endGroup();
}

GifMkSetting::GifMkSetting() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()) {
}

void GifMkSetting::load() {
    m_Settings.beginGroup("GifMk");
    m_OutPath = m_Settings.value(QStringLiteral("OutPath"), Default::GifMk::outPath).toString();
    m_OutFmt = m_Settings.value(QStringLiteral("OutFmt"), Default::GifMk::outFormat).toString();
    m_LastAddFilePath = m_Settings.value(QStringLiteral("LastAddFilePath"), Default::GifMk::lastAddFilePath).toString();
    m_LastAddFolderPath = m_Settings.value(QStringLiteral("LastAddFolderPath"), Default::GifMk::lastAddFolderPath).toString();
    m_Width = m_Settings.value(QStringLiteral("Width"), Default::GifMk::width).toInt();
    m_Height = m_Settings.value(QStringLiteral("Height"), Default::GifMk::height).toInt();
    m_Quality = m_Settings.value(QStringLiteral("Quality"), Default::GifMk::quality).toInt();
    m_Fps = m_Settings.value(QStringLiteral("Fps"), Default::GifMk::fps).toInt();
    m_Repeat = m_Settings.value(QStringLiteral("Repeat"), Default::GifMk::repeat).toBool();
    m_Settings.endGroup();
}

QString GifMkSetting::getOutPath() const {
    return m_OutPath;
}

void GifMkSetting::setOutPath(const QString &path) {
    m_OutPath = path;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("OutPath"), m_OutPath);
    m_Settings.endGroup();
}

QString GifMkSetting::getOutFmt() const {
    return m_OutFmt;
}

void GifMkSetting::setOutFmt(const QString &fmt) {
    m_OutFmt = fmt;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("OutFmt"), m_OutFmt);
    m_Settings.endGroup();
}

QString GifMkSetting::getLastAddFilePath() const {
    return m_LastAddFilePath;
}

void GifMkSetting::setLastAddFilePath(const QString &path) {
    m_LastAddFilePath = path;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("LastAddFilePath"), m_LastAddFilePath);
    m_Settings.endGroup();
}

QString GifMkSetting::getLastAddFolderPath() const {
    return m_LastAddFolderPath;
}

void GifMkSetting::setLastAddFolderPath(const QString &path) {
    m_LastAddFolderPath = path;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("LastAddFolderPath"), m_LastAddFolderPath);
    m_Settings.endGroup();
}

int GifMkSetting::getWidth() const {
    return m_Width;
}

void GifMkSetting::setWidth(int w) {
    m_Width = w;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("Width"), m_Width);
    m_Settings.endGroup();
}

int GifMkSetting::getHeight() const {
    return m_Height;
}

void GifMkSetting::setHeight(int h) {
    m_Height = h;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("Height"), m_Height);
    m_Settings.endGroup();
}

int GifMkSetting::getQuality() const {
    return m_Quality;
}

void GifMkSetting::setQuality(int q) {
    m_Quality = q;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("Quality"), m_Quality);
    m_Settings.endGroup();
}

int GifMkSetting::getFps() const {
    return m_Fps;
}

void GifMkSetting::setFps(int f) {
    m_Fps = f;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("Fps"), m_Fps);
    m_Settings.endGroup();
}

bool GifMkSetting::getRepeat() const {
    return m_Repeat;
}

void GifMkSetting::setRepeat(bool b) {
    m_Repeat = b;
    m_Settings.beginGroup("GifMk");
    m_Settings.setValue(QStringLiteral("Repeat"), m_Repeat);
    m_Settings.endGroup();
}

BgRmSetting::BgRmSetting() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()) {
}

void BgRmSetting::load() {
    m_Settings.beginGroup("BgRm");
    m_OutPath = m_Settings.value(QStringLiteral("OutPath"), Default::BgRm::outPath).toString();
    m_OutFmt = m_Settings.value(QStringLiteral("OutFmt"), Default::BgRm::outFormat).toString();
    m_LastAddFilePath = m_Settings.value(QStringLiteral("LastAddFilePath"), Default::BgRm::lastAddFilePath).toString();
    m_LastAddFolderPath = m_Settings.value(QStringLiteral("LastAddFolderPath"), Default::BgRm::lastAddFolderPath).toString();
    m_Settings.endGroup();
}

QString BgRmSetting::getOutPath() const {
    return m_OutPath;
}

void BgRmSetting::setOutPath(const QString &path) {
    m_OutPath = path;
    m_Settings.beginGroup("BgRm");
    m_Settings.setValue(QStringLiteral("OutPath"), m_OutPath);
    m_Settings.endGroup();
}

QString BgRmSetting::getOutFmt() const {
    return m_OutFmt;
}

void BgRmSetting::setOutFmt(const QString &fmt) {
    m_OutFmt = fmt;
    m_Settings.beginGroup("BgRm");
    m_Settings.setValue(QStringLiteral("OutFmt"), m_OutFmt);
    m_Settings.endGroup();
}

QString BgRmSetting::getLastAddFilePath() const {
    return m_LastAddFilePath;
}

void BgRmSetting::setLastAddFilePath(const QString &path) {
    m_LastAddFilePath = path;
    m_Settings.beginGroup("BgRm");
    m_Settings.setValue(QStringLiteral("LastAddFilePath"), m_LastAddFilePath);
    m_Settings.endGroup();
}

QString BgRmSetting::getLastAddFolderPath() const {
    return m_LastAddFolderPath;
}

void BgRmSetting::setLastAddFolderPath(const QString &path) {
    m_LastAddFolderPath = path;
    m_Settings.beginGroup("BgRm");
    m_Settings.setValue(QStringLiteral("LastAddFolderPath"), m_LastAddFolderPath);
    m_Settings.endGroup();
}

UpscSetting::UpscSetting() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()) {
}

void UpscSetting::load() {
    m_Settings.beginGroup("Upsc");
    m_OutPath = m_Settings.value(QStringLiteral("OutPath"), Default::Upsc::outPath).toString();
    m_OutFmt = m_Settings.value(QStringLiteral("OutFmt"), Default::Upsc::outFormat).toString();
    m_Scale = m_Settings.value(QStringLiteral("Scale"), Default::Upsc::scale).toInt();
    m_DoubleUpscale = m_Settings.value(QStringLiteral("DoubleUpscale"), Default::Upsc::doubleUpscale).toBool();
    m_ModelType = m_Settings.value(QStringLiteral("ModelType"), Default::Upsc::modelType).toInt();
    m_Settings.endGroup();
}

QString UpscSetting::getOutPath() const {
    return m_OutPath;
}

void UpscSetting::setOutPath(const QString &path) {
    m_OutPath = path;
    m_Settings.beginGroup("Upsc");
    m_Settings.setValue(QStringLiteral("OutPath"), m_OutPath);
    m_Settings.endGroup();
}

QString UpscSetting::getOutFmt() const {
    return m_OutFmt;
}

void UpscSetting::setOutFmt(const QString &fmt) {
    m_OutFmt = fmt;
    m_Settings.beginGroup("Upsc");
    m_Settings.setValue(QStringLiteral("OutFmt"), m_OutFmt);
    m_Settings.endGroup();
}

int UpscSetting::getScale() const {
    return m_Scale;
}

void UpscSetting::setScale(int s) {
    m_Scale = s;
    m_Settings.beginGroup("Upsc");
    m_Settings.setValue(QStringLiteral("Scale"), m_Scale);
    m_Settings.endGroup();
}

bool UpscSetting::getDoubleUpscale() const {
    return m_DoubleUpscale;
}

void UpscSetting::setDoubleUpscale(bool b) {
    m_DoubleUpscale = b;
    m_Settings.beginGroup("Upsc");
    m_Settings.setValue(QStringLiteral("DoubleUpscale"), m_DoubleUpscale);
    m_Settings.endGroup();
}

int UpscSetting::getModelType() const {
    return m_ModelType;
}

void UpscSetting::setModelType(int type) {
    m_ModelType = type;
    m_Settings.beginGroup("Upsc");
    m_Settings.setValue(QStringLiteral("ModelType"), m_ModelType);
    m_Settings.endGroup();
}

EraseSetting::EraseSetting() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()) {
}

void EraseSetting::load() {
    m_Settings.beginGroup("Erase");
    m_OutPath = m_Settings.value(QStringLiteral("OutPath"), Default::Erase::outPath).toString();
    m_OutFmt = m_Settings.value(QStringLiteral("OutFmt"), Default::Erase::outFormat).toString();
    m_Settings.endGroup();
}

QString EraseSetting::getOutPath() const {
    return m_OutPath;
}

void EraseSetting::setOutPath(const QString &path) {
    m_OutPath = path;
    m_Settings.beginGroup("Erase");
    m_Settings.setValue(QStringLiteral("OutPath"), m_OutPath);
    m_Settings.endGroup();
}

QString EraseSetting::getOutFmt() const {
    return m_OutFmt;
}

void EraseSetting::setOutFmt(const QString &fmt) {
    m_OutFmt = fmt;
    m_Settings.beginGroup("Erase");
    m_Settings.setValue(QStringLiteral("OutFmt"), m_OutFmt);
    m_Settings.endGroup();
}

CropSetting::CropSetting() :
    m_Settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(),
               QApplication::applicationDisplayName()) {
}

void CropSetting::load() {
    m_Settings.beginGroup("Crop");
    m_OutPath = m_Settings.value(QStringLiteral("OutPath"), Default::Crop::outPath).toString();
    m_OutFmt = m_Settings.value(QStringLiteral("OutFmt"), Default::Crop::outFormat).toString();
    m_Settings.endGroup();
}

QString CropSetting::getOutPath() const {
    return m_OutPath;
}

void CropSetting::setOutPath(const QString &path) {
    m_OutPath = path;
    m_Settings.beginGroup("Crop");
    m_Settings.setValue(QStringLiteral("OutPath"), m_OutPath);
    m_Settings.endGroup();
}

QString CropSetting::getOutFmt() const {
    return m_OutFmt;
}

void CropSetting::setOutFmt(const QString &fmt) {
    m_OutFmt = fmt;
    m_Settings.beginGroup("Crop");
    m_Settings.setValue(QStringLiteral("OutFmt"), m_OutFmt);
    m_Settings.endGroup();
}

Settings::Settings() {
    m_ConvSetting = new ConvSetting();
    m_CompSetting = new CompSetting();
    m_GifMkSetting = new GifMkSetting();
    m_BgRmSetting = new BgRmSetting();
    m_UpscSetting = new UpscSetting();
    m_EraseSetting = new EraseSetting();
    m_CropSetting = new CropSetting();
}

void Settings::load() {
    m_ConvSetting->load();
    m_CompSetting->load();
    m_GifMkSetting->load();
    m_BgRmSetting->load();
    m_UpscSetting->load();
    m_EraseSetting->load();
    m_CropSetting->load();
}

ConvSetting *Settings::getConvSetting() const {
    return m_ConvSetting;
}

CompSetting *Settings::getCompSetting() const {
    return m_CompSetting;
}

GifMkSetting *Settings::getGifMkSetting() const {
    return m_GifMkSetting;
}

BgRmSetting *Settings::getBgRmSetting() const {
    return m_BgRmSetting;
}

UpscSetting *Settings::getUpscSetting() const {
    return m_UpscSetting;
}

EraseSetting *Settings::getEraseSetting() const {
    return m_EraseSetting;
}

CropSetting *Settings::getCropSetting() const {
    return m_CropSetting;
}