/*
 * @Author: weick
 * @Date: 2023-12-21 23:57:42
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-15 23:17:39
 */

#include "inc/conversioncontroller.h"
#include "inc/signals.h"
#include <QFileDialog>
#include <QStandardPaths>

ConversionController::ConversionController() {
    m_ConversionWindow = new ConversionWindow;
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

void ConversionController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigOpenConvFileDialog, this, &ConversionController::openConvFileDialog);
    connect(Signals::getInstance(), &Signals::sigDelConvFile, this, &ConversionController::delConvData);
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
        conversionData.m_DelIcon = QPixmap(":/agui/res/image/delete1-24.png");
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
