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
        QPixmap pixmap = QPixmap(filePath);
        pixmap = pixmap.scaled(QSize(148, 148), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/agui/res/image/delete1-24.png");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.delete_icon = delIcon;
        datas_.append(data);
    }
    window_->changeFileListData(datas_);
    window_->setFileListCurrentIndex(datas_.count() - 1);
    emit Signals::getInstance()->sigFileListItemSelected(datas_.last());
}

void EditController::deleteData(const QString filePath) {
    int currentIndex = window_->fileListCurrentIndex();
    auto filePathMatches = [](const Data &cd, QString filePath) {
        return cd.file_path == filePath;
    };

    // 查找当前选中的数据在 datas_ 中的位置
    auto it = std::find_if(datas_.begin(), datas_.end(), std::bind(filePathMatches, std::placeholders::_1, filePath));
    // 如果当前选中的数据存在且被删除，则更新当前索引
    if (it != datas_.end()) {
        if (std::distance(datas_.begin(), it) == currentIndex) {
            currentIndex = -1; // 将当前索引标记为无效，以便后续重新选中
        }
    }

    datas_.erase(std::remove_if(datas_.begin(), datas_.end(), std::bind(filePathMatches, std::placeholders::_1, filePath)), datas_.end());
    window_->changeFileListData(datas_);

    // 计算删除后的选中索引
    int n = currentIndex;
    if (currentIndex == -1) {
        // 如果删除的是当前选中的数据，则选中索引为原当前索引
        n = std::min(static_cast<int>(datas_.size()) - 1, currentIndex);
    }

    window_->setFileListCurrentIndex(n);

    if (n != -1) {
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