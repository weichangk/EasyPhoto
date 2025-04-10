#include "bgremover/presenter.h"
#include "bgremover/repository.h"

#include <QFileInfo>

BackgroungRemoverPresenter::BackgroungRemoverPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

BackgroungRemoverPresenter::~BackgroungRemoverPresenter() {
}

QList<SBGRemoverData> BackgroungRemoverPresenter::datas() {
    BackgroungRemoverRepository *rep = dynamic_cast<BackgroungRemoverRepository *>(repository());
    return rep->datas();
}

void BackgroungRemoverPresenter::appendData(const QStringList filePaths) {
    QList<SBGRemoverData> tempDatas;
    for (const QString &filePath : filePaths) {
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SBGRemoverData data;
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
        tempDatas.append(data);
    }
    BackgroungRemoverRepository *rep = dynamic_cast<BackgroungRemoverRepository *>(repository());
    rep->appendData(tempDatas);
}

void BackgroungRemoverPresenter::deleteData(const QStringList filePaths) {
    BackgroungRemoverRepository *rep = dynamic_cast<BackgroungRemoverRepository *>(repository());
    rep->deleteData(filePaths);
    for(auto path : filePaths) {
        filePathsSet.remove(path);
    }
}

void BackgroungRemoverPresenter::deleteCheckedData() {
    BackgroungRemoverRepository *rep = dynamic_cast<BackgroungRemoverRepository *>(repository());
    rep->deleteCheckedData();
    for(auto data : rep->datas()) {
        if(data.is_checked) {
            filePathsSet.remove(data.file_path);
        }
    }
}

void BackgroungRemoverPresenter::clearData() {
    BackgroungRemoverRepository *rep = dynamic_cast<BackgroungRemoverRepository *>(repository());
    rep->clearData();
    filePathsSet.clear();
}

void BackgroungRemoverPresenter::switchCheckedData(const QString filePath) {
    BackgroungRemoverRepository *rep = dynamic_cast<BackgroungRemoverRepository *>(repository());
    rep->switchCheckedData(filePath);
}

void BackgroungRemoverPresenter::checkedAllData(bool checked) {
    BackgroungRemoverRepository *rep = dynamic_cast<BackgroungRemoverRepository *>(repository());
    rep->checkedAllData(checked);
}