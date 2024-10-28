/*
 * @Author: weick
 * @Date: 2024-03-05 23:03:24
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 20:48:56
 */

#include "inc/compressmanager.h"
#include <QMimeDatabase>
#include <QApplication>
#include <QDir>
#include <QProcess>
#include <QUuid>
#include <QDebug>

namespace imagecompression {
bool isDestSmallerThanSrc(QString src, QString dst) {
    int srcFileSize = 0;
    int dstFileSize = 0;
    QFile srcFile(src);
    if (srcFile.open(QIODevice::ReadOnly)) {
        srcFileSize = srcFile.size();
        srcFile.close();
    }
    QFile dstFile(dst);
    if (dstFile.open(QIODevice::ReadOnly)) {
        dstFileSize = dstFile.size();
        dstFile.close();
    }
    return dstFileSize <= srcFileSize;
}

CompressManager &CompressManager::instance() {
    static CompressManager _instance;
    return _instance;
}

CompressManager::CompressManager() {
    init();
}

void CompressManager::init() {
    m_CompressProtocals.push_back(new GUEETZLIProtocal);
    // m_CompressProtocals.push_back(new CJPEGProtocal);
    m_CompressProtocals.push_back(new PNGQUANTProtocal);
    // m_CompressProtocals.push_back(new OPTIPNGProtocal);
    m_CompressProtocals.push_back(new CWEBPProtocal);
    m_CompressProtocals.push_back(new GIFSICLEProtocal);
}

Result CompressManager::doCompress(const QString &src, const QString &dst, const Param &params) {
    Result result = {0};
    QMimeDatabase db;
    QMimeType mimeType = db.mimeTypeForFile(src, QMimeDatabase::MatchContent);
    QString name = mimeType.name();
    QStringList suffixes = mimeType.suffixes();
    QString preferredSuffix = mimeType.preferredSuffix();
    for (std::vector<CompressProtocal *>::iterator it = m_CompressProtocals.begin(); it != m_CompressProtocals.end(); ++it) {
        if ((*it)->compressable(preferredSuffix)) {
            result = (*it)->compress(src, dst, params);
            if (result.success) {
                break;
            }
        }
    }
    return result;
}

bool GUEETZLIProtocal::compressable(const QString &preferredSuffix) {
    return preferredSuffix == "jpeg";
}

Result GUEETZLIProtocal::compress(const QString &src, const QString &dst, const Param &params) {
    Result result = {0};
    QString libPath = QApplication::applicationDirPath() + "/imagelib/guetzli/";
    libPath = QDir::toNativeSeparators(libPath + "guetzli.exe");
    if (!QFile::exists(libPath)) {
        qDebug() << "guetzli.exe not exist!";
        return result;
    }
    QProcess process(this);
    QStringList args;
    args << "-quality" << QString::number(params.jpeg_quality) << src << dst;
    process.start(libPath, args);
    process.waitForFinished(300000);
    result.success = process.exitCode() == QProcess::ExitStatus::NormalExit;
    return result;
}

bool CJPEGProtocal::compressable(const QString &preferredSuffix) {
    return preferredSuffix == "jpeg";
}

Result CJPEGProtocal::compress(const QString &src, const QString &dst, const Param &params) {
    Result result = {0};
    QString libPath = QApplication::applicationDirPath() + "/imagelib/jpeg/";
    libPath = QDir::toNativeSeparators(libPath + "cjpeg.exe");
    if (!QFile::exists(libPath)) {
        qDebug() << "cjpeg.exe not exist!";
        return result;
    }
    QString tempBmpFile = toBitmap(src);
    if (!QFile::exists(tempBmpFile)) {
        qDebug() << "create temp bitmap file failed!";
        return result;
    }
    QProcess process(this);
    QStringList args;
    args << "-quality" << QString::number(params.jpeg_quality) << "-outfile" << dst << tempBmpFile;
    process.start(libPath, args);
    process.waitForFinished(300000);
    result.success = process.exitCode() == QProcess::ExitStatus::NormalExit;
    QFile::remove(tempBmpFile);
    if (result.success) {
        result.success = isDestSmallerThanSrc(src, dst);
    }
    return result;
}

QString CJPEGProtocal::toBitmap(const QString &src) {
    if (!QFile::exists(src)) {
        return "";
    }
    QString tempPath = QDir::tempPath();
    QString tempBmpFile = QDir::toNativeSeparators(tempPath + "/" + QUuid::createUuid().toString() + ".bmp");
    QImage img(src);
    QImage newImg = img.convertToFormat(QImage::Format_RGB32, Qt::ImageConversionFlag::AutoColor);
    newImg.save(tempBmpFile);
    return tempBmpFile;
}

bool PNGQUANTProtocal::compressable(const QString &preferredSuffix) {
    return preferredSuffix == "png";
}

Result PNGQUANTProtocal::compress(const QString &src, const QString &dst, const Param &params) {
    Result result = {0};
    QString libPath = QApplication::applicationDirPath() + "/imagelib/pngquant/";
    libPath = QDir::toNativeSeparators(libPath + "pngquant.exe");
    if (!QFile::exists(libPath)) {
        qDebug() << "pngquant.exe not exist!";
        return result;
    }
    QProcess process(this);
    QStringList args;
    args << "--force"
         << "--skip-if-larger"
         << "--quality" << QString::number(params.png_quality) << src << "--output" << dst;
    process.start(libPath, args);
    process.waitForFinished(300000);
    result.success = process.exitCode() == QProcess::ExitStatus::NormalExit;
    return result;
}

bool OPTIPNGProtocal::compressable(const QString &preferredSuffix) {
    return preferredSuffix == "png";
}

Result OPTIPNGProtocal::compress(const QString &src, const QString &dst, const Param &params) {
    Result result = {0};
    QString libPath = QApplication::applicationDirPath() + "/imagelib/png/";
    libPath = QDir::toNativeSeparators(libPath + "optipng.exe");
    if (!QFile::exists(libPath)) {
        qDebug() << "optipng.exe not exist!";
        return result;
    }
    QProcess process(this);
    QStringList args;
    args << "-ol" << src << "out" << dst;
    process.start(libPath, args);
    process.waitForFinished(300000);
    result.success = process.exitCode() == QProcess::ExitStatus::NormalExit;
    return result;
}

bool CWEBPProtocal::compressable(const QString &preferredSuffix) {
    return preferredSuffix == "webp";
}

Result CWEBPProtocal::compress(const QString &src, const QString &dst, const Param &params) {
    Result result = {0};
    QString libPath = QApplication::applicationDirPath() + "/imagelib/cwebp/";
    libPath = QDir::toNativeSeparators(libPath + "cwebp.exe");
    if (!QFile::exists(libPath)) {
        qDebug() << "cwebp.exe not exist!";
        return result;
    }
    QProcess process(this);
    QStringList args;
    args << "-q" << QString::number(params.webp_quality) << src << "-o" << dst;
    process.start(libPath, args);
    process.waitForFinished(300000);
    result.success = process.exitCode() == QProcess::ExitStatus::NormalExit;
    return result;
}

bool GIFSICLEProtocal::compressable(const QString &preferredSuffix) {
    return preferredSuffix == "gif";
}

Result GIFSICLEProtocal::compress(const QString &src, const QString &dst, const Param &params) {
    Result result = {0};
    QString libPath = QApplication::applicationDirPath() + "/imagelib/gif/";
    libPath = QDir::toNativeSeparators(libPath + "gifsicle.exe");
    if (!QFile::exists(libPath)) {
        qDebug() << "gifsicle.exe not exist!";
        return result;
    }
    QProcess process(this);
    QStringList args;
    QString quality = QString("--lossy=%1").arg(QString::number(params.gif_quality));
    args << "-02" << quality << src << "-o" << dst << "--verbose";
    process.start(libPath, args);
    process.waitForFinished(300000);
    result.success = process.exitCode() == QProcess::ExitStatus::NormalExit;
    return result;
}
}