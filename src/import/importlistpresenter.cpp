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