#include "inc/imageupscaylcontroller.h"
#include "inc/signals.h"
#include <QFileDialog>
#include <QStandardPaths>

namespace imageupscayl {
ImageUpscaylController::ImageUpscaylController() {
    init();
    sigConnect();
}

ImageUpscaylController::~ImageUpscaylController() {
}

void ImageUpscaylController::showWindow() {
    window_->show();
}

void ImageUpscaylController::closeWindow() {
    window_->close();
}

void ImageUpscaylController::init() {
    window_ = new ImageUpscaylWindow;
}

void ImageUpscaylController::sigConnect() {
    connect(SIGNALS, &Signals::sigOpenFileDialog, this, &ImageUpscaylController::openFileDialog);
    connect(SIGNALS, &Signals::sigDeleteFile, this, &ImageUpscaylController::deleteData);
    connect(SIGNALS, &Signals::sigClickedFile, this, &ImageUpscaylController::clickedData);
    connect(SIGNALS, &Signals::sigStatus, this, &ImageUpscaylController::status);
    connect(SIGNALS, &Signals::sigDeleteAll, this, &ImageUpscaylController::deleteAll);
}

void ImageUpscaylController::openFileDialog(QWidget *parent) {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(parent, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        addData(selectedFiles);
    }
}

void ImageUpscaylController::addData(const QStringList filePaths) {
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
        emit SIGNALS->sigListItemDataSelected(&datas_.last());
    }
}

void ImageUpscaylController::deleteData(const QString filePath) {
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
        emit SIGNALS->sigListItemDataSelected(&datas_[n]);
    }
}

void ImageUpscaylController::clickedData(const QString filePath) {
    auto filePathMatches = [](const Data &cd, QString filePath) {
        return cd.file_path == filePath;
    }; 
    auto it = std::find_if(datas_.begin(), datas_.end(), [&](const Data& d) {
        return filePathMatches(d, filePath);
    });
    if (it != datas_.end()) {
        imageupscayl::Data* dataPtr = &(*it); 
        emit SIGNALS->sigListItemDataSelected(dataPtr);
    }
}

void ImageUpscaylController::status(Status state) {
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

void ImageUpscaylController::start() {
}

void ImageUpscaylController::finished() {
}

void ImageUpscaylController::cancel() {
}

void ImageUpscaylController::deleteAll() {
    datas_.clear();
    window_->changeFileListData(datas_);
}

void ImageUpscaylController::dataUpdate(Data data) {
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

bool ImageUpscaylController::checkAddedData(const QString filePath) {
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

} // namespace imageupscayl