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
namespace Conv {
static QString outPath = defOutPath("Conv");
static QString outFormat = "png";
static QString lastAddFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
static QString lastAddFolderPath = QDir::homePath();
} // namespace Conv

namespace Cmp {
static QString outPath = defOutPath("Cmp");
static QString outFormat = "sameassource";
static QString lastAddFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
static QString lastAddFolderPath = QDir::homePath();
static int quality = 60;
} // namespace Cmp

namespace GifMk {
static QString outPath = defOutPath("GifMk");
static QString outFormat = "gif";
static QString lastAddFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
static QString lastAddFolderPath = QDir::homePath();
static int width = 640;
static int height = 640;
static int quality = 100;
static int fps = 25;
static bool repeat = true;
} // namespace GifMk

namespace BgRm {
static QString outPath = defOutPath("BgRm");
static QString outFormat = "png";
static QString lastAddFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
static QString lastAddFolderPath = QDir::homePath();
} // namespace BgRm

namespace Upsc {
static QString outPath = defOutPath("Upsc");
static QString outFormat = "png";
} // namespace Upsc

namespace Erase {
static QString outPath = defOutPath("Erase");
static QString outFormat = "png";
} // namespace Erase

namespace Crop {
static QString outPath = defOutPath("Crop");
static QString outFormat = "png";
} // namespace Erase

} // namespace Default

class ConvSetting {
public:
    ConvSetting();
    void load();
    QString getOutPath() const;
    void setOutPath(const QString &path);
    QString getOutFmt();
    void setOutFmt(const QString &fmt);
    QString getLastAddFilePath();
    void setLastAddFilePath(const QString &path);
    QString getLastAddFolderPath();
    void setLastAddFolderPath(const QString &path);

private:
    QSettings m_Settings;
    QString m_OutPath;
    QString m_OutFmt;
    QString m_LastAddFilePath;
    QString m_LastAddFolderPath;
};

class CmpSetting {
public:
    CmpSetting();
    void load();
    QString getOutPath() const;
    void setOutPath(const QString &path);
    QString getOutFmt();
    void setOutFmt(const QString &fmt);
    QString getLastAddFilePath();
    void setLastAddFilePath(const QString &path);
    QString getLastAddFolderPath();
    void setLastAddFolderPath(const QString &path);
    int getQuality();
    void setQuality(int q);

private:
    QSettings m_Settings;
    QString m_OutPath;
    QString m_OutFmt;
    QString m_LastAddFilePath;
    QString m_LastAddFolderPath;
    int m_Quality;
};

class GifMkSetting {
public:
    GifMkSetting();
    void load();
    QString getOutPath() const;
    void setOutPath(const QString &path);
    QString getOutFmt();
    void setOutFmt(const QString &fmt);
    QString getLastAddFilePath();
    void setLastAddFilePath(const QString &path);
    QString getLastAddFolderPath();
    void setLastAddFolderPath(const QString &path);
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    int getQuality();
    void setQuality(int q);
    int getFps();
    void setFps(int f);
    bool getRepeat();
    void setRepeat(bool b);

private:
    QSettings m_Settings;
    QString m_OutPath;
    QString m_OutFmt;
    QString m_LastAddFilePath;
    QString m_LastAddFolderPath;
    int m_Width;
    int m_Height;
    int m_Quality;
    int m_Fps;
    bool m_Repeat;
};

class BgRmSetting {
public:
    BgRmSetting();
    void load();
    QString getOutPath() const;
    void setOutPath(const QString &path);
    QString getOutFmt();
    void setOutFmt(const QString &fmt);
    QString getLastAddFilePath();
    void setLastAddFilePath(const QString &path);
    QString getLastAddFolderPath();
    void setLastAddFolderPath(const QString &path);

private:
    QSettings m_Settings;
    QString m_OutPath;
    QString m_OutFmt;
    QString m_LastAddFilePath;
    QString m_LastAddFolderPath;
};

class UpscSetting {
public:
    UpscSetting();
    void load();
    QString getOutPath() const;
    void setOutPath(const QString &path);
    QString getOutFmt();
    void setOutFmt(const QString &fmt);

private:
    QSettings m_Settings;
    QString m_OutPath;
    QString m_OutFmt;
};

class EraseSetting {
public:
    EraseSetting();
    void load();
    QString getOutPath() const;
    void setOutPath(const QString &path);
    QString getOutFmt();
    void setOutFmt(const QString &fmt);

private:
    QSettings m_Settings;
    QString m_OutPath;
    QString m_OutFmt;
};

class CropSetting {
public:
    CropSetting();
    void load();
    QString getOutPath() const;
    void setOutPath(const QString &path);
    QString getOutFmt();
    void setOutFmt(const QString &fmt);

private:
    QSettings m_Settings;
    QString m_OutPath;
    QString m_OutFmt;
};

class Settings : public Singlton<Settings> {
public:
    Settings();
    void load();
    ConvSetting *getConvSetting() const;
    CmpSetting *getCmpSetting() const;
    GifMkSetting *getGifMkSetting() const;
    BgRmSetting *getBgRmSetting() const;
    UpscSetting *getUpscSetting() const;
    EraseSetting *getEraseSetting() const;
    CropSetting *getCropSetting() const;

private:
    ConvSetting *m_ConvSetting;
    CmpSetting *m_CmpSetting;
    GifMkSetting *m_GifMkSetting;
    BgRmSetting *m_BgRmSetting;
    UpscSetting *m_UpscSetting;
    EraseSetting *m_EraseSetting;
    CropSetting *m_CropSetting;
};

#define SETTINGS Settings::getInstance()
