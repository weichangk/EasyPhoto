/*
 * @Author: weick
 * @Date: 2024-03-05 23:03:24
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-05 23:27:52
 */

#include "inc/compressmanager.h"
#include <QMimeDatabase>
#include <QApplication>
#include <QDir>
#include <QProcess>

CompressManager &CompressManager::instance() {
    static CompressManager _instance;
    return _instance;
}

CompressManager::CompressManager() {
    init();
}

bool CompressManager::compressable(const QString &preferredSuffix) {
    return preferredSuffix == "jpeg";
}

CompressResult CompressManager::compress(const QString &src, const QString &dst, const CompressParam &params) {
    CompressResult result = {0};
    QString libPath = QApplication::applicationDirPath() + "/imagelib/guetzli/";
    libPath = QDir::toNativeSeparators(libPath + "guetzli.exe");
    if (!QFile::exists(libPath)) {
        qDebug() << "guetzli.exe not exist!";
        return result;
    }
    QProcess *process = new QProcess(this);
    QStringList args;
    args << "-quality" << QString::number(params.jpeg_quality) << src << dst;
    process->start(libPath, args);
    process->waitForFinished(300000);
    result.success = process->exitCode() == QProcess::ExitStatus::NormalExit;
    return result;
}

void CompressManager::init() {
}

CompressResult CompressManager::doCompress(const QString &src, const QString &dst, const CompressParam &params) {
    CompressResult result = {0};
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
