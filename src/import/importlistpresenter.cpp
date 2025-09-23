#include "import/importlistpresenter.h"
#include "import/importlistrepository.h"

#include <QFileInfo>

ImportListPresenter::ImportListPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

ImportListPresenter::~ImportListPresenter() {
}

QList<SImageData> ImportListPresenter::getDatas() {
    ImportListRepository *rep = dynamic_cast<ImportListRepository *>(repository());
    return rep->getDatas();
}

void ImportListPresenter::appendData(const QStringList filePaths) {
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
        pixmap = pixmap.scaled(QSize(112, 72), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/icon16_close");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.delete_icon = delIcon;
        tempDatas.append(data);
    }
    ImportListRepository *rep = dynamic_cast<ImportListRepository *>(repository());
    rep->appendData(tempDatas);
}

void ImportListPresenter::deleteData(const QStringList filePaths) {
    ImportListRepository *rep = dynamic_cast<ImportListRepository *>(repository());
    rep->deleteData(filePaths);
    for(auto path : filePaths) {
        filePathsSet.remove(path);
    }
}

void ImportListPresenter::clearData() {
    ImportListRepository *rep = dynamic_cast<ImportListRepository *>(repository());
    rep->clearData();
    filePathsSet.clear();
}

int ImportListPresenter::getDataIndex(const QString filePath) {
    ImportListRepository *rep = dynamic_cast<ImportListRepository *>(repository());
    return rep->getDataIndex(filePath);
}

void ImportListPresenter::appendData(const QList<SImageData> datas) {
    ImportListRepository *rep = dynamic_cast<ImportListRepository *>(repository());
    rep->appendData(datas);
}

TaskResult<SImportFileResult<QList<SImageData>>> ImportListPresenter::importFileAsync(AsyncTask<SImportFileData, SImportFileResult<QList<SImageData>>> *self) {
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
        data.output_format = SETTINGS->getConvSetting()->getOutFmt();
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