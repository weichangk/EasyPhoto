#include "enhancement/repository.h"

#include <QCoreApplication>

EnhancementRepository::EnhancementRepository() {
    m_pImportListRepository = new ImportListRepository();
}

EnhancementRepository::~EnhancementRepository() {
}

QList<SEnhanceModelData> EnhancementRepository::getModelDatas() {
    QString execDir = QCoreApplication::applicationDirPath();
    return {
        SEnhanceModelData{
            0,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SEnhanceModelData{
            1,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SEnhanceModelData{
            2,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SEnhanceModelData{
            3,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SEnhanceModelData{
            4,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
        SEnhanceModelData{
            5,
            "sample1",
            QString("%1/sample1.webp").arg(execDir),
            QPixmap(QString("%1/sample1.webp").arg(execDir)),
        },
    };
}

QString EnhancementRepository::getSampleImage1Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample1.webp").arg(execDir);
}

QString EnhancementRepository::getSampleImage2Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample2.webp").arg(execDir);
}

ImportListRepository *EnhancementRepository::getImportListRepository() {
    return m_pImportListRepository;
}