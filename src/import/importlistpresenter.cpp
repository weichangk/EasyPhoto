#include "import/importlistpresenter.h"
#include "import/importlistrepository.h"

#include <QFileInfo>

ImportListPresenter::ImportListPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

ImportListPresenter::~ImportListPresenter() {
}

QList<SImportListItem> ImportListPresenter::getDatas() {
    ImportListRepository *rep = dynamic_cast<ImportListRepository *>(repository());
    return rep->getDatas();
}

void ImportListPresenter::appendData(const QStringList filePaths) {
    QList<SImportListItem> tempDatas;
    for (const QString &filePath : filePaths) {
        // if (filePathsSet.contains(filePath)) {
        //     continue;
        // } else {
        //     filePathsSet.insert(filePath);
        // }
        SImportListItem data;
        data.path = filePath;
        data.name = QFileInfo(filePath).fileName();
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
}

void ImportListPresenter::clearData() {
    ImportListRepository *rep = dynamic_cast<ImportListRepository *>(repository());
    rep->clearData();
}