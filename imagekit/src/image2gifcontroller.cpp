/*
 * @Author: weick
 * @Date: 2024-03-23 10:53:08
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 08:02:10
 */

#include "inc/image2gifcontroller.h"
#include "inc/signals.h"
#include <QFileDialog>
#include <QStandardPaths>

namespace image2gif {
Image2GifController::Image2GifController() {
    init();
    sigConnect();
}

Image2GifController::~Image2GifController() {
}

void Image2GifController::showWindow() {
    window_->show();
}

void Image2GifController::closeWindow() {
    window_->close();
}

void Image2GifController::init() {
    window_ = new Image2GifWindow;
}

void Image2GifController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigOpenFileDialog, this, &Image2GifController::openFileDialog);
    connect(Signals::getInstance(), &Signals::sigDeleteFile, this, &Image2GifController::deleteData);
    connect(Signals::getInstance(), &Signals::sigClickedFile, this, &Image2GifController::clickedData);
    connect(Signals::getInstance(), &Signals::sigStatus, this, &Image2GifController::status);
    connect(Signals::getInstance(), &Signals::sigDeleteAll, this, &Image2GifController::deleteAll);
}

void Image2GifController::openFileDialog(QWidget *parent) {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(parent, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        addData(selectedFiles);
    }
}

void Image2GifController::addData(const QStringList filePaths) {
    int oldCout = datas_.count();
    for (const QString &filePath : filePaths) {
        if(checkAddedData(filePath)) {
            continue;
        }
        Data data;
        data.file_path = filePath;
        data.file_name = QFileInfo(filePath).fileName();
        QPixmap pixmap = QPixmap(filePath);
        pixmap = pixmap.scaled(QSize(120, 90), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/agui/res/image/delete1-24.png");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.delete_icon = delIcon;
        QPixmap beforeAddIcon = QPixmap(":/agui/res/image/delete1-24.png");
        data.before_add_icon = beforeAddIcon;
        QPixmap afterAddIcon = QPixmap(":/agui/res/image/delete1-24.png");
        data.after_add_icon = afterAddIcon;
        datas_.append(data);
    }
    if (oldCout < datas_.count()) {
        window_->changeFileListData(datas_);
        window_->setFileListCurrentIndex(datas_.count() - 1);
        emit Signals::getInstance()->sigListItemDataSelected(&datas_.last());
    }
}

void Image2GifController::deleteData(const QString filePath) {
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

void Image2GifController::clickedData(const QString filePath) {
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

void Image2GifController::status(Status state) {
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

void Image2GifController::start() {
}

void Image2GifController::finished() {
}

void Image2GifController::cancel() {
}

void Image2GifController::deleteAll() {
    datas_.clear();
    window_->changeFileListData(datas_);
}

void Image2GifController::dataUpdate(Data data) {
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

bool Image2GifController::checkAddedData(const QString filePath) {
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

} // namespace image2gif