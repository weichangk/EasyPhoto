/*
 * @Author: weick
 * @Date: 2024-03-23 10:53:08
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 20:27:23
 */

#include "inc/editcontroller.h"
#include "inc/signals.h"
#include <QFileDialog>
#include <QStandardPaths>

namespace imageedit {
EditController::EditController() {
    init();
    sigConnect();
}

EditController::~EditController() {
}

void EditController::showWindow() {
    window_->show();
}

void EditController::closeWindow() {
    window_->close();
}

void EditController::init() {
    window_ = new EditWindow;
}

void EditController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigOpenFileDialog, this, &EditController::openFileDialog);
    connect(Signals::getInstance(), &Signals::sigDeleteFile, this, &EditController::deleteData);
    connect(Signals::getInstance(), &Signals::sigStatus, this, &EditController::status);
    connect(Signals::getInstance(), &Signals::sigDeleteAll, this, &EditController::deleteAll);
}

void EditController::openFileDialog(QWidget *parent) {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(parent, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        addData(selectedFiles);
    }
}

void EditController::addData(const QStringList filePaths) {
    for (const QString &filePath : filePaths) {
        Data data;
        data.file_path = filePath;
        data.file_name = QFileInfo(filePath).fileName();
        QPixmap delIcon = QPixmap(":/agui/res/image/delete1-24.png");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.delete_icon = delIcon;
        QImage image(filePath);
        data.crop_rect = QRectF(0, 0, image.width(), image.height());
        datas_.append(data);
    }
    window_->changeFileListData(datas_);
    window_->setFileListCurrentIndex(datas_.count() - 1);
    emit Signals::getInstance()->sigFileListItemSelected(datas_.last());
}

void EditController::deleteData(const QString filePath) {
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
        emit Signals::getInstance()->sigFileListItemSelected(datas_[n]);
    }
}

void EditController::status(Status state) {
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

void EditController::start() {
    // auto task = [&]() {
    //     Image image;
    //     QString filePath;
    //     QFileInfo fileInfo;
    //     foreach (const auto &data, m_ConvDatas) {
    //         fileInfo = AFileMgr::fileInfo(data.file_path);
    //         if (fileInfo.exists() && data.is_checked) {
    //             filePath = AFileMgr::joinPathAndFileName(SETTINGS->conversionOutPath(), QString("%1.%2").arg(fileInfo.baseName()).arg(SETTINGS->conversionOutFormat()));
    //             AFileMgr::renameIfExists(filePath);
    //             image.read(data.file_path.toStdString());
    //             image.write(filePath.toStdString());
    //         }
    //     }
    // };
    // m_ConvWatcher.setFuture(QtConcurrent::run(task));
}

void EditController::finished() {
}
void EditController::cancel() {
}

void EditController::deleteAll() {
    datas_.clear();
    window_->changeFileListData(datas_);
}
} // namespace imageedit