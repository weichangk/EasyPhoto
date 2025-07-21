#include "conversion/presenter.h"
#include "conversion/repository.h"

#include <QFileInfo>

ConversionPresenter::ConversionPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

ConversionPresenter::~ConversionPresenter() {
}

QList<SConversionData> ConversionPresenter::datas() {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    return rep->datas();
}

void ConversionPresenter::updateData(const SConversionData &data) {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->updateData(data);
}

void ConversionPresenter::updateData(const QString filePath, const SConversionData &data) {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->updateData(filePath, data);
}

void ConversionPresenter::appendData(const QStringList filePaths) {
    QList<SConversionData> tempDatas;
    for (const QString &filePath : filePaths) {
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SConversionData data;
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
        data.output_format = SETTINGS->conversionOutFormat();
        data.state_icons = {
            {EConvState_Waiting, QPixmap(":/qtmaterial/img/vcu/dark/icon/icon_basic/icon16/icon16_status_waiting.png")},
            {EConvState_Loading, QPixmap(":/qtmaterial/img/vcu/dark/icon/icon_basic/icon16/icon16_status_loading.png")},
            {EConvState_Success, QPixmap(":/qtmaterial/img/vcu/dark/icon/icon_basic/icon16/icon16_status_success.png")},
            {EConvState_Fail, QPixmap(":/qtmaterial/img/vcu/dark/icon/icon_basic/icon16/icon16_status_danger.png")}
        };
        tempDatas.append(data);
    }
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->appendData(tempDatas);
}

void ConversionPresenter::deleteData(const QStringList filePaths) {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->deleteData(filePaths);
    for(auto path : filePaths) {
        filePathsSet.remove(path);
    }
}

void ConversionPresenter::deleteCheckedData() {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->deleteCheckedData();
    for(auto data : rep->datas()) {
        if(data.is_checked) {
            filePathsSet.remove(data.file_path);
        }
    }
}

void ConversionPresenter::clearData() {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->clearData();
    filePathsSet.clear();
}

void ConversionPresenter::switchCheckedData(const QString filePath) {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->switchCheckedData(filePath);
}

void ConversionPresenter::checkedAllData(bool checked) {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->checkedAllData(checked);
}

TaskResult<SImportFileResult<QList<SConversionData>>> ConversionPresenter::importFileAsync(AsyncTask<SImportFileData, SImportFileResult<QList<SConversionData>>> *self) {
    QList<SConversionData> tempDatas;
    int index = 0;
    for (const QString &filePath : self->getData().value.filePaths) {
        if(self->isCanceled()) {
            return TaskResult<SImportFileResult<QList<SConversionData>>>::Failure("");
        }
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SConversionData data;
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
        data.output_format = SETTINGS->conversionOutFormat();
        data.state_icons = {
            {EConvState_Waiting, QPixmap(":/qtmaterial/img/vcu/dark/icon/icon_basic/icon16/icon16_status_waiting.png")},
            {EConvState_Loading, QPixmap(":/qtmaterial/img/vcu/dark/icon/icon_basic/icon16/icon16_status_loading.png")},
            {EConvState_Success, QPixmap(":/qtmaterial/img/vcu/dark/icon/icon_basic/icon16/icon16_status_success.png")},
            {EConvState_Fail, QPixmap(":/qtmaterial/img/vcu/dark/icon/icon_basic/icon16/icon16_status_danger.png")}
        };
        tempDatas.append(data);
        self->progress(++index, "Adding images:" + data.file_name.toStdString());
    }

    SImportFileResult<QList<SConversionData>> result = {tempDatas, 100};
    return TaskResult<SImportFileResult<QList<SConversionData>>>::Success(result);
}

void ConversionPresenter::appendData(const QList<SConversionData> datas) {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->appendData(datas);
}