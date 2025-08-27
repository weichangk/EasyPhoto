#include "compression/presenter.h"
#include "compression/repository.h"

#include <QFileInfo>

CompressionPresenter::CompressionPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

CompressionPresenter::~CompressionPresenter() {
}

QList<SCompressionData> CompressionPresenter::datas() {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    return rep->datas();
}

void CompressionPresenter::updateData(const SCompressionData &data) {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->updateData(data);
}

void CompressionPresenter::updateData(const QString filePath, const SCompressionData &data) {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->updateData(filePath, data);
}

void CompressionPresenter::appendData(const QStringList filePaths) {
    QList<SCompressionData> tempDatas;
    for (const QString &filePath : filePaths) {
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SCompressionData data;
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
            {ECompreState_Waiting, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_waiting.png")},
            {ECompreState_Loading, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_loading.png")},
            {ECompreState_Success, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_success.png")},
            {ECompreState_Fail, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_danger.png")}
        };
        tempDatas.append(data);
    }
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->appendData(tempDatas);
}

void CompressionPresenter::deleteData(const QStringList filePaths) {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->deleteData(filePaths);
    for (auto path : filePaths) {
        filePathsSet.remove(path);
    }
}

void CompressionPresenter::deleteCheckedData() {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->deleteCheckedData();
    for (auto data : rep->datas()) {
        if (data.is_checked) {
            filePathsSet.remove(data.file_path);
        }
    }
}

void CompressionPresenter::clearData() {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->clearData();
    filePathsSet.clear();
}

void CompressionPresenter::switchCheckedData(const QString filePath) {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->switchCheckedData(filePath);
}

void CompressionPresenter::checkedAllData(bool checked) {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->checkedAllData(checked);
}

TaskResult<SImportFileResult<QList<SCompressionData>>> CompressionPresenter::importFileAsync(AsyncTask<SImportFileData, SImportFileResult<QList<SCompressionData>>> *self) {
    QList<SCompressionData> tempDatas;
    int index = 0;
    for (const QString &filePath : self->getData().value.filePaths) {
        if(self->isCanceled()) {
            return TaskResult<SImportFileResult<QList<SCompressionData>>>::Failure("");
        }
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SCompressionData data;
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
            {ECompreState_Waiting, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_waiting.png")},
            {ECompreState_Loading, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_loading.png")},
            {ECompreState_Success, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_success.png")},
            {ECompreState_Fail, QPixmap(":/QtmImg/img/dark/icon/icon_basic/icon16/icon16_status_danger.png")}
        };
        tempDatas.append(data);
        self->progress(++index, "Adding images:" + data.file_name.toStdString());
    }

    SImportFileResult<QList<SCompressionData>> result = {tempDatas, 100};
    return TaskResult<SImportFileResult<QList<SCompressionData>>>::Success(result);
}

void CompressionPresenter::appendData(const QList<SCompressionData> datas) {
    CompressionRepository *rep = dynamic_cast<CompressionRepository *>(repository());
    rep->appendData(datas);
}