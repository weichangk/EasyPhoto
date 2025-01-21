#include "conversion/presenter.h"
#include "conversion/repository.h"

#include <QFileInfo>

ConversionPresenter::ConversionPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

ConversionPresenter::~ConversionPresenter() {
}

QList<Data> ConversionPresenter::datas() {
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    return rep->datas();
}

void ConversionPresenter::appendData(const QStringList filePaths) {
    QList<Data> tempDatas;
    for (const QString &filePath : filePaths) {
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        Data data;
        data.file_path = filePath;
        data.file_name = QFileInfo(filePath).fileName();
        QPixmap pixmap = QPixmap(filePath);
        pixmap = pixmap.scaled(QSize(148, 148), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.thumbnail = pixmap;
        QPixmap delIcon = QPixmap(":/agui/res/image/delete1-24.png");
        delIcon = delIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.delete_icon = delIcon;
        QPixmap checkedIcon = QPixmap(":/agui/res/image/checked1-24.png");
        checkedIcon = checkedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.checked_icon = checkedIcon;
        QPixmap unCheckedIcon = QPixmap(":/agui/res/image/unchecked1-24.png");
        unCheckedIcon = unCheckedIcon.scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.unchecked_icon = unCheckedIcon;
        data.is_checked = true;
        tempDatas.append(data);
    }
    ConversionRepository *rep = dynamic_cast<ConversionRepository *>(repository());
    rep->appendData(tempDatas);
}