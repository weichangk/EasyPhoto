#include "comp/presenter.h"
#include "comp/repository.h"

#include <QFileInfo>

CompPresenter::CompPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

CompPresenter::~CompPresenter() {
}

QList<SImageData> CompPresenter::datas() {
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    return rep->datas();
}

void CompPresenter::updateData(const SImageData &data) {
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    rep->updateData(data);
}

void CompPresenter::updateData(const QString filePath, const SImageData &data) {
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    rep->updateData(filePath, data);
}

void CompPresenter::appendData(const QStringList filePaths) {
    QList<SImageData> tempDatas;
    for (const QString &filePath : filePaths) {
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SImageData data;
        data.file_path = filePath;
        data.file_name = QFileInfo(filePath).fileName();
        QPixmap pixmap = QPixmap(filePath);
        pixmap = pixmap.scaled(QSize(200 + 8 - 4 - 12, 200 + 8 - 24 - 12), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/icon16_close");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.delete_icon = delIcon;
        QPixmap checkedIcon = QPixmap(":/icon16_checkbox_checked");
        checkedIcon = checkedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.checked_icon = checkedIcon;
        QPixmap unCheckedIcon = QPixmap(":/icon16_checkbox_checked");
        unCheckedIcon = unCheckedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.unchecked_icon = unCheckedIcon;
        data.is_checked = true;
        data.resolution = QSize(pixmap.width(), pixmap.height());
        QFileInfo fileInfo(filePath);
        QString size = "0";
        if (fileInfo.exists() && fileInfo.isFile()) {
            float fileSize = fileInfo.size() / 1024.0 / 1024.0;
            QString sizeStr = QString("%1 MB").arg(QString::number(fileSize, 'f', 2));
            size = sizeStr;
        }
        data.intput_size = size;
        data.output_size = size;
        data.state_icons = {
            {EImageState_Waiting, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_waiting.png")},
            {EImageState_Loading, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_loading.png")},
            {EImageState_Success, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_success.png")},
            {EImageState_Fail, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_danger.png")}
        };
        tempDatas.append(data);
    }
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    rep->appendData(tempDatas);
}

void CompPresenter::deleteData(const QStringList filePaths) {
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    rep->deleteData(filePaths);
    for (auto path : filePaths) {
        filePathsSet.remove(path);
    }
}

void CompPresenter::deleteCheckedData() {
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    rep->deleteCheckedData();
    for (auto data : rep->datas()) {
        if (data.is_checked) {
            filePathsSet.remove(data.file_path);
        }
    }
}

void CompPresenter::clearData() {
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    rep->clearData();
    filePathsSet.clear();
}

void CompPresenter::switchCheckedData(const QString filePath) {
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    rep->switchCheckedData(filePath);
}

void CompPresenter::checkedAllData(bool checked) {
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    rep->checkedAllData(checked);
}

TaskResult<SImportFileResult<QList<SImageData>>> CompPresenter::importFileAsync(AsyncTask<SImportFileData, SImportFileResult<QList<SImageData>>> *self) {
    QList<SImageData> tempDatas;
    int index = 0;
    for (const QString &filePath : self->getData().value.filePaths) {
        if(self->isCanceled()) {
            return TaskResult<SImportFileResult<QList<SImageData>>>::Failure("");
        }
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SImageData data;
        data.file_path = filePath;
        data.file_name = QFileInfo(filePath).fileName();
        QPixmap pixmap = QPixmap(filePath);
        QPixmap thPixmap = pixmap.scaled(QSize(200 + 8 - 4 - 12, 200 + 8 - 24 - 12), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.thumbnail = thPixmap;
        QPixmap delIcon = QPixmap(":/icon16_close");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.delete_icon = delIcon;
        QPixmap checkedIcon = QPixmap(":/icon16_checkbox_checked");
        checkedIcon = checkedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.checked_icon = checkedIcon;
        QPixmap unCheckedIcon = QPixmap(":/icon16_checkbox_checked");
        unCheckedIcon = unCheckedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.unchecked_icon = unCheckedIcon;
        data.is_checked = true;
        data.resolution = QSize(pixmap.width(), pixmap.height());
        QFileInfo fileInfo(filePath);
        QString size = "0";
        if (fileInfo.exists() && fileInfo.isFile()) {
            float fileSize = fileInfo.size() / 1024.0 / 1024.0;
            QString sizeStr = QString("%1 MB").arg(QString::number(fileSize, 'f', 2));
            size = sizeStr;
        }
        data.intput_size = size;
        data.output_size = size;
        data.state_icons = {
            {EImageState_Waiting, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_waiting.png")},
            {EImageState_Loading, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_loading.png")},
            {EImageState_Success, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_success.png")},
            {EImageState_Fail, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_danger.png")}
        };
        tempDatas.append(data);
        self->progress(++index, "Adding images:" + data.file_name.toStdString());
    }

    SImportFileResult<QList<SImageData>> result = {tempDatas, 100};
    return TaskResult<SImportFileResult<QList<SImageData>>>::Success(result);
}

void CompPresenter::appendData(const QList<SImageData> datas) {
    CompRepository *rep = dynamic_cast<CompRepository *>(repository());
    rep->appendData(datas);
}