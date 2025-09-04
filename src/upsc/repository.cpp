#include "upsc/repository.h"

#include <QCoreApplication>

UpscRepository::UpscRepository() {
    m_pImportListRepository = new ImportListRepository();
}

UpscRepository::~UpscRepository() {
}

QList<SUpscModelData> UpscRepository::getModelDatas() {
    QString execDir = QCoreApplication::applicationDirPath();
    return {
        SUpscModelData{
            0,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SUpscModelData{
            1,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SUpscModelData{
            2,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SUpscModelData{
            3,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SUpscModelData{
            4,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SUpscModelData{
            5,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
    };
}

QString UpscRepository::getSampleImage1Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample1.webp").arg(execDir);
}

QString UpscRepository::getSampleImage2Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample2.webp").arg(execDir);
}

ImportListRepository *UpscRepository::getImportListRepository() {
    return m_pImportListRepository;
}