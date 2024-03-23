/*
 * @Author: weick
 * @Date: 2024-01-07 23:46:03
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 23:14:32
 */

#include "inc/compressioncontroller.h"
#include "inc/signals.h"
#include "inc/settings.h"
#include "inc/models.h"
#include "inc/compressmanager.h"
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
        imagecompression::Data compressionData;
        compressionData.file_path = filePath;
        compressionData.file_name = QFileInfo(filePath).fileName();
        QPixmap pixmap = QPixmap(filePath);
        pixmap = pixmap.scaled(QSize(148, 148), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        compressionData.thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/agui/res/image/delete1-24.png");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        compressionData.delete_icon = delIcon;
        QPixmap checkedIcon = QPixmap(":/agui/res/image/checked1-24.png");
        checkedIcon = checkedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        compressionData.checked_icon = checkedIcon;
        QPixmap unCheckedIcon = QPixmap(":/agui/res/image/unchecked1-24.png");
        unCheckedIcon = unCheckedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        compressionData.unchecked_icon = unCheckedIcon;
        compressionData.is_checked = true;
        m_CompressDatas.append(compressionData);
    }
    m_CompressionWindow->changeData(m_CompressDatas);
}

void CompressionController::delCompressData(const QString filePath) {
    auto filePathMatches = [](const imagecompression::Data &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    m_CompressDatas.erase(std::remove_if(m_CompressDatas.begin(), m_CompressDatas.end(), std::bind(filePathMatches, std::placeholders::_1, filePath)), m_CompressDatas.end());
    m_CompressionWindow->changeData(m_CompressDatas);
}

void CompressionController::compressStatus(imagecompression::Status state) {
    switch (state) {
    case imageconversion::Status::NONE:
        break;
    case imageconversion::Status::START:
        compressStart();
        break;
    case imageconversion::Status::FINISHED:
        compressFinished();
        break;
    case imageconversion::Status::CANCEL:
        compressCancel();
        break;
    }
}

void CompressionController::compressStart() {
    QString filePath;
    QFileInfo fileInfo;
    foreach (const auto &data, m_CompressDatas) {
        fileInfo = AFileMgr::fileInfo(data.file_path);
        if (fileInfo.exists() && data.is_checked) {
            filePath = AFileMgr::joinPathAndFileName(SETTINGS->compressOutPath(), QString("%1.%2").arg(fileInfo.baseName()).arg(fileInfo.completeSuffix()));
            AFileMgr::renameIfExists(filePath);
            imagecompression::Param param;
            param.jpeg_quality = SETTINGS->compressQuality();
            param.png_quality = SETTINGS->compressQuality();
            param.gif_quality = SETTINGS->compressQuality();
            param.webp_quality = SETTINGS->compressQuality();
            CompressManager::instance().doCompress(data.file_path, filePath, param);
        }
    }
}

void CompressionController::compressFinished() {
}

void CompressionController::compressCancel() {
}

void CompressionController::switchChecked(const QString filePath, const bool checked) {
    auto filePathMatches = [](const imagecompression::Data &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_CompressDatas.begin(), m_CompressDatas.end(), std::bind(filePathMatches, std::placeholders::_1, filePath));
    if (it != m_CompressDatas.end()) {
        it->is_checked = !it->is_checked;
    }
    m_CompressionWindow->changeData(m_CompressDatas);
}

void CompressionController::allChecked(bool checked) {
    for (auto &data : m_CompressDatas) {
        data.is_checked = checked;
    }
    m_CompressionWindow->changeData(m_CompressDatas);
}

void CompressionController::delByChecked() {
    m_CompressDatas.erase(std::remove_if(m_CompressDatas.begin(), m_CompressDatas.end(), [](const imagecompression::Data &cd) {
                              return cd.is_checked == true;
                          }),
                          m_CompressDatas.end());
    m_CompressionWindow->changeData(m_CompressDatas);
}
