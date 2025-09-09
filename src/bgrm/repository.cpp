#include "bgrm/repository.h"

#include <QCoreApplication>
#include <QDir>"

BgRmRepository::BgRmRepository() {
    m_pImportListRepository = new ImportListRepository();
}

BgRmRepository::~BgRmRepository() {
}

QString BgRmRepository::getSampleImage1Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample1.webp").arg(execDir);
}

QString BgRmRepository::getSampleImage2Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample2.webp").arg(execDir);
}

QList<SBgImgData> BgRmRepository::getBgImgDataDatas(EBgImgType type) {
    QString imgTypeDir = "general";
    if (type == EBgImgType_Custom) {
        return QList<SBgImgData>();
    } else if (type == EBgImgType_General) {
        imgTypeDir = "general";
        if(m_BgGeneralImgDatas.size() > 0) {
            return m_BgGeneralImgDatas;
        }
    } else if (type == EBgImgType_Scene) {
        imgTypeDir = "scene";
        if(m_BgSceneImgDatas.size() > 0) {
            return m_BgSceneImgDatas;
        }
    }
    QString execDir = QCoreApplication::applicationDirPath();
    QList<SBgImgData> datas;
    QDir dir(QString("%1/bgrmimg/%2").arg(execDir).arg(imgTypeDir));
    QStringList files = dir.entryList(QDir::Files);
    for (const QString &file : files) {
        QFileInfo fileInfo(file);
        SBgImgData data;
        data.file_name = fileInfo.fileName();
        data.file_path = dir.absoluteFilePath(file);
        data.thumbnail = QPixmap(data.file_path).scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        data.is_checked = false;
        if(type == EBgImgType_General) {
            m_BgGeneralImgDatas.append(data);
        } else if(type == EBgImgType_Scene) {
            m_BgSceneImgDatas.append(data);
        }
    }
    if (type == EBgImgType_General) {
        return m_BgGeneralImgDatas;
    } else if (type == EBgImgType_Scene) {
        return m_BgSceneImgDatas;
    }
}

ImportListRepository *BgRmRepository::getImportListRepository() {
    return m_pImportListRepository;
}