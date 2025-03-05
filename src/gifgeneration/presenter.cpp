#include "gifgeneration/presenter.h"
#include "gifgeneration/repository.h"
#include "message/funcchangemessage.h"

#include <QFileInfo>

GifGenerationPresenter::GifGenerationPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

GifGenerationPresenter::~GifGenerationPresenter() {
}

QList<SGifGenerationData> GifGenerationPresenter::datas() {
    GifGenerationRepository *rep = dynamic_cast<GifGenerationRepository *>(repository());
    return rep->datas();
}

void GifGenerationPresenter::appendData(const QStringList filePaths) {
    QList<SGifGenerationData> tempDatas;
    for (const QString &filePath : filePaths) {
        if (filePathsSet.contains(filePath)) {
            continue;
        } else {
            filePathsSet.insert(filePath);
        }
        SGifGenerationData data;
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
    GifGenerationRepository *rep = dynamic_cast<GifGenerationRepository *>(repository());
    rep->appendData(tempDatas);
}

void GifGenerationPresenter::deleteData(const QStringList filePaths) {
    GifGenerationRepository *rep = dynamic_cast<GifGenerationRepository *>(repository());
    rep->deleteData(filePaths);
    for(auto path : filePaths) {
        filePathsSet.remove(path);
    }
}

void GifGenerationPresenter::deleteCheckedData() {
    GifGenerationRepository *rep = dynamic_cast<GifGenerationRepository *>(repository());
    rep->deleteCheckedData();
    for(auto data : rep->datas()) {
        if(data.is_checked) {
            filePathsSet.remove(data.file_path);
        }
    }
}

void GifGenerationPresenter::clearData() {
    GifGenerationRepository *rep = dynamic_cast<GifGenerationRepository *>(repository());
    rep->clearData();
    filePathsSet.clear();
}

void GifGenerationPresenter::funcChangeSubjectAttach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.attach(observer);
}

void GifGenerationPresenter::funcChangeSubjectDetach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.detach(observer);
}

bool GifGenerationPresenter::handleMessage(IMessage *message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        funcChangeSubjectNotify((EFunc)msg->code());
    }
    return false;
}

void GifGenerationPresenter::funcChangeSubjectNotify(EFunc func) {
    m_pFuncChangeObserver.notify(&IFuncChangeObserver::funcChangeHandle, func);
}