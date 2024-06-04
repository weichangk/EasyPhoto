/*
 * @Author: weick 
 * @Date: 2024-06-04 08:00:52 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:00:52 
 */

#include "inc/imageenhancementcontroller.h"
#include "inc/signals.h"
#include <QFileDialog>
#include <QStandardPaths>

namespace imageenhancement {
ImageEnhancementController::ImageEnhancementController() {
    init();
    sigConnect();
}

ImageEnhancementController::~ImageEnhancementController() {
}

void ImageEnhancementController::showWindow() {
    window_->show();
}

void ImageEnhancementController::closeWindow() {
    window_->close();
}

void ImageEnhancementController::init() {
    window_ = new ImageEnhancementWindow;
}

void ImageEnhancementController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigOpenFileDialog, this, &ImageEnhancementController::openFileDialog);
    connect(Signals::getInstance(), &Signals::sigDeleteFile, this, &ImageEnhancementController::deleteData);
    connect(Signals::getInstance(), &Signals::sigClickedFile, this, &ImageEnhancementController::clickedData);
    connect(Signals::getInstance(), &Signals::sigStatus, this, &ImageEnhancementController::status);
    connect(Signals::getInstance(), &Signals::sigDeleteAll, this, &ImageEnhancementController::deleteAll);
}

void ImageEnhancementController::openFileDialog(QWidget *parent) {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(parent, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        addData(selectedFiles);
    }
}

void ImageEnhancementController::addData(const QStringList filePaths) {
    int oldCout = datas_.count();
    for (const QString &filePath : filePaths) {
        if(checkAddedData(filePath)) {
            continue;
        }
        Data data;
        data.file_path = filePath;
        data.file_name = QFileInfo(filePath).fileName();
        QPixmap delIcon = QPixmap(":/agui/res/image/delete1-24.png");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.delete_icon = delIcon;
        datas_.append(data);
    }
    if (oldCout < datas_.count()) {
        window_->changeFileListData(datas_);
        window_->setFileListCurrentIndex(datas_.count() - 1);
        emit Signals::getInstance()->sigListItemDataSelected(&datas_.last());
    }
}

void ImageEnhancementController::deleteData(const QString filePath) {
    // 点击删除时已经改变了currentIndex
    int currentIndex = window_->fileListCurrentIndex();
    auto filePathMatches = [](const Data &cd, QString filePath) {
        return cd.file_path == filePath;
    };

    datas_.erase(std::remove_if(datas_.begin(), datas_.end(), std::bind(filePathMatches, std::placeholders::_1, filePath)), datas_.end());
    window_->changeFileListData(datas_);

    int n = currentIndex;
    n = std::min(static_cast<int>(datas_.size()) - 1, currentIndex);

    if (n != -1) {
        window_->setFileListCurrentIndex(n);
        emit Signals::getInstance()->sigListItemDataSelected(&datas_[n]);
    }
}

void ImageEnhancementController::clickedData(const QString filePath) {
    auto filePathMatches = [](const Data &cd, QString filePath) {
        return cd.file_path == filePath;
    }; 
    auto it = std::find_if(datas_.begin(), datas_.end(), [&](const Data& d) {
        return filePathMatches(d, filePath);
    });
    if (it != datas_.end()) {
        emit Signals::getInstance()->sigListItemDataSelected(it);
    }
}

void ImageEnhancementController::status(Status state) {
    switch (state) {
    case Status::NONE:
        break;
    case Status::START:
        start();
        break;
    case Status::FINISHED:
        finished();
        break;
    case Status::CANCEL:
        cancel();
        break;
    }
}

void ImageEnhancementController::start() {
}

void ImageEnhancementController::finished() {
}

void ImageEnhancementController::cancel() {
}

void ImageEnhancementController::deleteAll() {
    datas_.clear();
    window_->changeFileListData(datas_);
}

void ImageEnhancementController::dataUpdate(Data data) {
    auto filePathMatches = [](const Data &cd, QString filePath) {
        return cd.file_path == filePath;
    }; 
    auto it = std::find_if(datas_.begin(), datas_.end(), [&](const Data& d) {
        return filePathMatches(d, data.file_path);
    });
    if (it != datas_.end()) {
        Data& foundData = *it;
        foundData = data;
        int currentIndex = window_->fileListCurrentIndex();
        window_->changeFileListData(datas_);
        window_->setFileListCurrentIndex(currentIndex);
    }
}

bool ImageEnhancementController::checkAddedData(const QString filePath) {
    auto filePathMatches = [](const Data &cd, QString filePath) {
        return cd.file_path == filePath;
    }; 
    auto it = std::find_if(datas_.begin(), datas_.end(), [&](const Data& d) {
        return filePathMatches(d, filePath);
    });
    if (it != datas_.end()) {
        return true;
    }
    return false;
}

} // namespace imageenhancement