/*
 * @Author: weick
 * @Date: 2024-01-07 23:46:03
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-07 23:46:51
 */

#include "inc/compressioncontroller.h"
#include "inc/signals.h"
#include "inc/settings.h"
#include "inc/models.h"
#include "../acore/inc/afoldermgr.h"
#include "../acore/inc/afilemgr.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QProcess>

CompressionController::CompressionController() {
    m_CompressionWindow = new CompressionWindow;
    init();
    sigConnect();
}

CompressionController::~CompressionController() {
}

void CompressionController::showWindow() {
    m_CompressionWindow->show();
}

void CompressionController::closeWindow() {
    m_CompressionWindow->close();
}

void CompressionController::init() {
    AFolderMgr::addFolder(SETTINGS->compressOutPath());
}

void CompressionController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigCompressOpenFileDialog, this, &CompressionController::openCompressFileDialog);
    connect(Signals::getInstance(), &Signals::sigCompressDelFile, this, &CompressionController::delCompressData);
    connect(Signals::getInstance(), &Signals::sigCompressStatus, this, &CompressionController::compressStatus);
    connect(Signals::getInstance(), &Signals::sigCompressSwitchChecked, this, &CompressionController::switchChecked);
    connect(Signals::getInstance(), &Signals::sigCompressAllChecked, this, &CompressionController::allChecked);
    connect(Signals::getInstance(), &Signals::sigCompressDelByChecked, this, &CompressionController::delByChecked);
}

void CompressionController::openCompressFileDialog(QWidget *parent) {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(parent, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        addCompressData(selectedFiles);
    }
}

void CompressionController::addCompressData(const QStringList filePaths) {
    for (const QString &filePath : filePaths) {
        Models::CompressionData compressionData;
        compressionData.m_FilePath = filePath;
        compressionData.m_FileName = QFileInfo(filePath).fileName();
        QPixmap pixmap = QPixmap(filePath);
        pixmap = pixmap.scaled(QSize(148, 148), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        compressionData.m_Thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/agui/res/image/delete1-24.png");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        compressionData.m_DelIcon = delIcon;
        QPixmap checkedIcon = QPixmap(":/agui/res/image/checked1-24.png");
        checkedIcon = checkedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        compressionData.m_CheckedIcon = checkedIcon;
        QPixmap unCheckedIcon = QPixmap(":/agui/res/image/unchecked1-24.png");
        unCheckedIcon = unCheckedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        compressionData.m_UnCheckedIcon = unCheckedIcon;
        compressionData.m_IsChecked = true;
        m_CompressDatas.append(compressionData);
    }
    m_CompressionWindow->changeData(m_CompressDatas);
}

void CompressionController::delCompressData(const QString filePath) {
    auto filePathMatches = [](const Models::CompressionData &cd, QString filePath) {
        return cd.m_FilePath == filePath;
    };
    m_CompressDatas.erase(std::remove_if(m_CompressDatas.begin(), m_CompressDatas.end(), std::bind(filePathMatches, std::placeholders::_1, filePath)), m_CompressDatas.end());
    m_CompressionWindow->changeData(m_CompressDatas);
}

void CompressionController::compressStatus(Models::CompressStatusEnum state) {
    switch (state) {
    case Models::ConvStatusEnum::None:
        break;
    case Models::ConvStatusEnum::Start:
        compressStart();
        break;
    case Models::ConvStatusEnum::Finished:
        compressFinished();
        break;
    case Models::ConvStatusEnum::Cancel:
        compressCancel();
        break;
    }
}

void CompressionController::compressStart() {
    QString filePath;
    QFileInfo fileInfo;
    foreach (const auto &data, m_CompressDatas) {
        fileInfo = AFileMgr::fileInfo(data.m_FilePath);
        if (fileInfo.exists() && data.m_IsChecked) {
            filePath = AFileMgr::joinPathAndFileName(SETTINGS->compressOutPath(), QString("%1.%2").arg(fileInfo.baseName()).arg(fileInfo.completeSuffix()));
            AFileMgr::renameIfExists(filePath);
            if (fileInfo.completeSuffix() == "png") {
                compressPNG(data.m_FilePath, filePath, SETTINGS->compressQuality());
            } else if (fileInfo.completeSuffix() == "jpeg") {
                compressJPEG(data.m_FilePath, filePath, SETTINGS->compressQuality());
            } else if (fileInfo.completeSuffix() == "webp") {
                compressWEBP(data.m_FilePath, filePath, SETTINGS->compressQuality());
            } else if (fileInfo.completeSuffix() == "gif") {
                compressGIF(data.m_FilePath, filePath, SETTINGS->compressQuality());
            }
        }
    }
}

void CompressionController::compressFinished() {
}

void CompressionController::compressCancel() {
}

void CompressionController::switchChecked(const QString filePath, const bool checked) {
    auto filePathMatches = [](const Models::CompressionData &cd, QString filePath) {
        return cd.m_FilePath == filePath;
    };
    auto it = std::find_if(m_CompressDatas.begin(), m_CompressDatas.end(), std::bind(filePathMatches, std::placeholders::_1, filePath));
    if (it != m_CompressDatas.end()) {
        it->m_IsChecked = !it->m_IsChecked;
    }
    m_CompressionWindow->changeData(m_CompressDatas);
}

void CompressionController::allChecked(bool checked) {
    for (auto &data : m_CompressDatas) {
        data.m_IsChecked = checked;
    }
    m_CompressionWindow->changeData(m_CompressDatas);
}

void CompressionController::delByChecked() {
    m_CompressDatas.erase(std::remove_if(m_CompressDatas.begin(), m_CompressDatas.end(), [](const Models::CompressionData &cd) {
                              return cd.m_IsChecked == true;
                          }),
                          m_CompressDatas.end());
    m_CompressionWindow->changeData(m_CompressDatas);
}

void CompressionController::compressPNG(const QString input, const QString out, const int quatily) {
    QProcess process;
    QString program = "imagelib/pngquant/pngquant.exe";
    QStringList arguments;
    arguments << "--quality=" + QString::number(quatily) + "-" + QString::number(quatily + 20) << input << "--output=" + out;
    process.start(program, arguments);
    QObject::connect(&process, &QProcess::finished, [&process]() {
        qDebug() << "Process finished with exit code:" << process.exitCode();
    });
}

void CompressionController::compressJPEG(const QString input, const QString out, const int quatily) {
    QProcess process;
    QString program = "imagelib/guetzli/guetzli.exe";
    QStringList arguments;
    arguments << "--quality=" + QString::number(quatily) << input << out;
    process.start(program, arguments);
    QObject::connect(&process, &QProcess::finished, [&process]() {
        qDebug() << "Process finished with exit code:" << process.exitCode();
    });
}

void CompressionController::compressWEBP(const QString input, const QString out, const int quatily) {
    QProcess process;
    QString program = "imagelib/cwebp/cwebp.exe";
    QStringList arguments;
    arguments << "-q" << QString::number(quatily) << input << "-o" << out;
    process.start(program, arguments);
    QObject::connect(&process, &QProcess::finished, [&process]() {
        qDebug() << "Process finished with exit code:" << process.exitCode();
    });
}

void CompressionController::compressGIF(const QString input, const QString out, const int quatily) {
}
