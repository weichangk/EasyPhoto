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

QString UpscRepository::getSampleImagePath(EUpscSmapleType type) {
    QString dir = "upscayl-standard-4x";
    switch (type) {
    case EUpscSmapleType_Standard:
        dir = "upscayl-standard-4x";
        break;
    case EUpscSmapleType_Lite:
        dir = "upscayl-lite-4x";
        break;
    case EUpscSmapleType_Fidelity:
        dir = "high-fidelity-4x";
        break;
    case EUpscSmapleType_Remacri:
        dir = "remacri-4x";
        break;
    case EUpscSmapleType_Ultramix:
        dir = "ultramix-balanced-4x";
        break;
    case EUpscSmapleType_Ultrasharp:
        dir = "ultrasharp-4x";
        break;
    case EUpscSmapleType_Digital:
        dir = "digital-art-4x";
        break;
    default:
        dir = "upscayl-standard-4x";
        break;
    }
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/res/upsc/model-comparison/%2/before.webp").arg(execDir).arg(dir);
}

ImportListRepository *UpscRepository::getImportListRepository() {
    return m_pImportListRepository;
}