/*
 * @Author: weick
 * @Date: 2023-12-21 23:57:42
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-15 23:17:39
 */

#include "inc/conversioncontroller.h"
#include "inc/signals.h"
#include "inc/settings.h"
#include "../acore/inc/afoldermgr.h"
#include "../acore/inc/afilemgr.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <Magick++.h>

using namespace Magick;
ConversionController::ConversionController() {
    m_ConversionWindow = new ConversionWindow;
    init();
    sigConnect();
}

ConversionController::~ConversionController() {
}

void ConversionController::showWindow() {
    m_ConversionWindow->show();
}

void ConversionController::closeWindow() {
    m_ConversionWindow->close();
}

void ConversionController::init() {
    AFolderMgr::addFolder(SETTINGS->conversionOutPath());
}

void ConversionController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigOpenConvFileDialog, this, &ConversionController::openConvFileDialog);
    connect(Signals::getInstance(), &Signals::sigDelConvFile, this, &ConversionController::delConvData);
    connect(Signals::getInstance(), &Signals::sigSatrtConv, this, &ConversionController::satrtConv);
    connect(Signals::getInstance(), &Signals::sigSwitchChecked, this, &ConversionController::switchChecked);
}

void ConversionController::openConvFileDialog(QWidget *parent) {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(parent, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        addConvData(selectedFiles);
    }
}

void ConversionController::addConvData(const QStringList filePaths) {
    for (const QString &filePath : filePaths) {
        ConversionData conversionData;
        conversionData.m_FilePath = filePath;
        conversionData.m_FileName = QFileInfo(filePath).fileName();
        QPixmap pixmap = QPixmap(filePath);
        pixmap = pixmap.scaled(QSize(148, 148), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        conversionData.m_Thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/agui/res/image/delete1-24.png");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        conversionData.m_DelIcon = delIcon;
        QPixmap checkedIcon = QPixmap(":/agui/res/image/checked1-24.png");
        checkedIcon = checkedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        conversionData.m_CheckedIcon = checkedIcon;
        QPixmap unCheckedIcon = QPixmap(":/agui/res/image/unchecked1-24.png");
        unCheckedIcon = unCheckedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        conversionData.m_UnCheckedIcon = unCheckedIcon;
        conversionData.m_IsChecked = true;
        m_ConvDatas.append(conversionData);
    }
    m_ConversionWindow->changeData(m_ConvDatas);
}

void ConversionController::delConvData(const QString filePath) {
    auto filePathMatches = [](const ConversionData &cd, QString filePath) {
        return cd.m_FilePath == filePath;
    };
    m_ConvDatas.erase(std::remove_if(m_ConvDatas.begin(), m_ConvDatas.end(), std::bind(filePathMatches, std::placeholders::_1, filePath)), m_ConvDatas.end());
    m_ConversionWindow->changeData(m_ConvDatas);
}

void ConversionController::satrtConv() {
    Image image;
    QString filePath;
    QFileInfo fileInfo;
    foreach(const auto &data, m_ConvDatas) {
        fileInfo = AFileMgr::fileInfo(data.m_FilePath);
        if(fileInfo.exists() && data.m_IsChecked) {
            filePath = AFileMgr::joinPathAndFileName(SETTINGS->conversionOutPath(), QString("%1.%2").arg(fileInfo.baseName()).arg(SETTINGS->conversionOutFormat()));
            AFileMgr::renameIfExists(filePath);
            image.read(data.m_FilePath.toStdString());
            image.write(filePath.toStdString());
        }
    }
}

void ConversionController::switchChecked(const QString filePath, const bool checked) {
    auto filePathMatches = [](const ConversionData &cd, QString filePath) {
        return cd.m_FilePath == filePath;
    };
    auto it = std::find_if(m_ConvDatas.begin(), m_ConvDatas.end(), std::bind(filePathMatches, std::placeholders::_1, filePath));
    if (it != m_ConvDatas.end()) {
        it->m_IsChecked = !it->m_IsChecked;
    }
    m_ConversionWindow->changeData(m_ConvDatas);
}
