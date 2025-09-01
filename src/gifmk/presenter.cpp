#include "gifmk/presenter.h"
#include "gifmk/repository.h"
#include "message/funcchangemessage.h"

#include <QFileInfo>

GifMkPresenter::GifMkPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

GifMkPresenter::~GifMkPresenter() {
}

QList<SGifMkData> GifMkPresenter::datas() {
    GifMkRepository *rep = dynamic_cast<GifMkRepository *>(repository());
    return rep->datas();
}

void GifMkPresenter::appendData(const QStringList filePaths) {
    QList<SGifMkData> tempDatas;
    for (const QString &filePath : filePaths) {
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SGifMkData data;
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
    GifMkRepository *rep = dynamic_cast<GifMkRepository *>(repository());
    rep->appendData(tempDatas);
}

void GifMkPresenter::deleteData(const QStringList filePaths) {
    GifMkRepository *rep = dynamic_cast<GifMkRepository *>(repository());
    rep->deleteData(filePaths);
    for(auto path : filePaths) {
        filePathsSet.remove(path);
    }
}

void GifMkPresenter::deleteCheckedData() {
    GifMkRepository *rep = dynamic_cast<GifMkRepository *>(repository());
    rep->deleteCheckedData();
    for(auto data : rep->datas()) {
        if(data.is_checked) {
            filePathsSet.remove(data.file_path);
        }
    }
}

void GifMkPresenter::clearData() {
    GifMkRepository *rep = dynamic_cast<GifMkRepository *>(repository());
    rep->clearData();
    filePathsSet.clear();
}

void GifMkPresenter::funcChangeSubjectAttach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.attach(observer);
}

void GifMkPresenter::funcChangeSubjectDetach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.detach(observer);
}

bool GifMkPresenter::handleMessage(IMessage *message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        funcChangeSubjectNotify((EFunc)msg->code());
    }
    return false;
}

void GifMkPresenter::funcChangeSubjectNotify(EFunc func) {
    m_pFuncChangeObserver.notify(&IFuncChangeObserver::funcChangeHandle, func);
}