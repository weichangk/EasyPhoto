#include "bgrm/presenter.h"
#include "bgrm/repository.h"

#include <QFileInfo>

BgRmPresenter::BgRmPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

BgRmPresenter::~BgRmPresenter() {
}

QList<SBgRmData> BgRmPresenter::datas() {
    BgRmRepository *rep = dynamic_cast<BgRmRepository *>(repository());
    return rep->datas();
}

void BgRmPresenter::appendData(const QStringList filePaths) {
    QList<SBgRmData> tempDatas;
    for (const QString &filePath : filePaths) {
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SBgRmData data;
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
    BgRmRepository *rep = dynamic_cast<BgRmRepository *>(repository());
    rep->appendData(tempDatas);
}

void BgRmPresenter::deleteData(const QStringList filePaths) {
    BgRmRepository *rep = dynamic_cast<BgRmRepository *>(repository());
    rep->deleteData(filePaths);
    for(auto path : filePaths) {
        filePathsSet.remove(path);
    }
}

void BgRmPresenter::deleteCheckedData() {
    BgRmRepository *rep = dynamic_cast<BgRmRepository *>(repository());
    rep->deleteCheckedData();
    for(auto data : rep->datas()) {
        if(data.is_checked) {
            filePathsSet.remove(data.file_path);
        }
    }
}

void BgRmPresenter::clearData() {
    BgRmRepository *rep = dynamic_cast<BgRmRepository *>(repository());
    rep->clearData();
    filePathsSet.clear();
}

void BgRmPresenter::switchCheckedData(const QString filePath) {
    BgRmRepository *rep = dynamic_cast<BgRmRepository *>(repository());
    rep->switchCheckedData(filePath);
}

void BgRmPresenter::checkedAllData(bool checked) {
    BgRmRepository *rep = dynamic_cast<BgRmRepository *>(repository());
    rep->checkedAllData(checked);
}