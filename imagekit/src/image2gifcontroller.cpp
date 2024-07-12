/*
 * @Author: weick
 * @Date: 2024-03-23 10:53:08
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-06 21:38:16
 */

#include "inc/image2gifcontroller.h"
#include "inc/signals.h"
#include "inc/settings.h"
#include "../acore/inc/afilemgr.h"
#include "../agui/inc/aloadingdialog.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <Magick++.h>

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
    connect(Signals::getInstance(), &Signals::sigListItemBeforeOrAfterAdd, this, &Image2GifController::listItemBeforeOrAfterAdd);
    connect(Signals::getInstance(), &Signals::sigListItemSwapedDatas, this, &Image2GifController::listItemSwapedUpdateDatas);
    connect(Signals::getInstance(), &Signals::sigExport, this, &Image2GifController::slotExport);
}

void Image2GifController::openFileDialog(QWidget *parent) {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(parent, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        appendData(selectedFiles);
    }
}

void Image2GifController::appendData(const QStringList filePaths) {
    int oldCout = datas_.count();

    std::function<void()> work = [&]() {
        for (const QString &filePath : filePaths) {
            if (checkAddedData(filePath)) {
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
            beforeAddIcon = beforeAddIcon.scaled(QSize(4, 8), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            data.before_add_icon = beforeAddIcon;
            QPixmap afterAddIcon = QPixmap(":/agui/res/image/delete1-24.png");
            afterAddIcon = afterAddIcon.scaled(QSize(4, 8), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            data.after_add_icon = afterAddIcon;
            datas_.append(data);
        }
    };

    ALoadingDialog loadingDialog;
    loadingDialog.setDoWork(work);
    loadingDialog.exec();

    if (oldCout < datas_.count()) {
        window_->changeFileListData(datas_);
        window_->setFileListCurrentIndex(datas_.count() - 1);
        emit Signals::getInstance() -> sigListItemDataSelected(&datas_.last());
    }
}

void Image2GifController::insertData(int index, const QStringList filePaths) {
    QList<Data> datas;
    int oldCout = datas_.count();

    std::function<void()> work = [&]() {
        for (const QString &filePath : filePaths) {
            if (checkAddedData(filePath)) {
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
            beforeAddIcon = beforeAddIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            data.before_add_icon = beforeAddIcon;
            QPixmap afterAddIcon = QPixmap(":/agui/res/image/delete1-24.png");
            afterAddIcon = afterAddIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            data.after_add_icon = afterAddIcon;
            datas.append(data);
        }

        // 在索引 index 位置插入新数据集合
        if (index >= 0 && index <= datas_.size()) {
            datas_.reserve(datas_.size() + datas.size()); // 预留空间以优化性能

            // 从后向前插入，以避免覆盖原有数据
            for (int i = datas.size() - 1; i >= 0; --i) {
                datas_.insert(index, datas.at(i));
            }
        }
    };

    ALoadingDialog loadingDialog;
    loadingDialog.setDoWork(work);
    loadingDialog.exec();

    if (oldCout < datas_.count()) {
        window_->changeFileListData(datas_);
        int iindex = index + datas.size() - 1;
        window_->setFileListCurrentIndex(iindex);
        emit Signals::getInstance()->sigListItemDataSelected(&datas_[iindex]);
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

void Image2GifController::listItemBeforeOrAfterAdd(int index, bool isBefore, QWidget *parent) {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(parent, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        insertData(isBefore ? index : index + 1, selectedFiles);
    }
}

void Image2GifController::listItemSwapedUpdateDatas(const QList<Data> &datas) {
    datas_ = datas;
}

void Image2GifController::slotExport() {
    generate();
}

void Image2GifController::generate() {
    std::vector<std::string> imageFiles;
    foreach(const auto &data,  datas_) {
        imageFiles.push_back(data.file_path.toStdString());
    }
    std::vector<Magick::Image> images;

    if (imageFiles.size() > 0) {
    } else {
    }

    try {
        for (const auto& file : imageFiles) {
            Magick::Image img;
            img.read(file);

            // 调整图像大小
            img.resize(Magick::Geometry(SETTINGS->gifWidth(), SETTINGS->gifHeight()));

            // 设置图像质量值为0-100，值越大质量越高
            img.quality(ImageQualityValueMap[(ImageQuality)SETTINGS->gifQuality()]);

            // 设置每帧之间的延迟时间
            img.animationDelay(1000 / GifFpsValueMap[(GifFps)SETTINGS->gifFps()]);

            images.push_back(img);
        }

        // 设置GIF循环次数
        for (auto& img : images) {
            // 无限循环
            img.animationIterations(SETTINGS->gifRepeat() ? 0 : 1); 
        }

        // 写入GIF文件
        QString filePath = AFileMgr::joinPathAndFileName(SETTINGS->gifOutpath(), QString("%1.%2").arg(QDateTime::currentDateTime().toString("MMddHHmmss")).arg("gif"));
        AFileMgr::renameIfExists(filePath);
        Magick::writeImages(images.begin(), images.end(), filePath.toStdString());
    }
    catch (Magick::Exception &error_) {
        qDebug() << "Image2GifController::generate error: " << error_.what();
    }
}

} // namespace image2gif