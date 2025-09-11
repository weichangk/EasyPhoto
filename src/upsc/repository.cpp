#include "upsc/repository.h"

#include <QCoreApplication>

UpscRepository::UpscRepository() {
    m_pImportListRepository = new ImportListRepository();
}

UpscRepository::~UpscRepository() {
}

QList<SUpscSelectModelData> UpscRepository::getSelectModelDatas() {
    if(!m_pSelectModelDatas.isEmpty()) {
        return m_pSelectModelDatas;
    }
    QString execDir = QCoreApplication::applicationDirPath();
    m_pSelectModelDatas =  {
        SUpscSelectModelData{
            0,
            EUpscSmapleType_Standard,
            "Upscayl Standard",
            "Suitable for most images.",
            QPixmap(QString("%1/res/upsc/model-comparison/upscayl-standard-4x/before.webp").arg(execDir)),
            QPixmap(QString("%1/res/upsc/model-comparison/upscayl-standard-4x/after.webp").arg(execDir)),
        },
        SUpscSelectModelData{
            1,
            EUpscSmapleType_Lite,
            "Upscayl Life",
            "Suitable for most images. High-speed upscaling with minimal quality loss.",
            QPixmap(QString("%1/res/upsc/model-comparison/upscayl-lite-4x/before.webp").arg(execDir)),
            QPixmap(QString("%1/res/upsc/model-comparison/upscayl-lite-4x/after.webp").arg(execDir)),
        },
        SUpscSelectModelData{
            2,
            EUpscSmapleType_Fidelity,
            "High Fidelity",
            "For all Kinds of images with a focus on realistic details and smooth textures.",
            QPixmap(QString("%1/res/upsc/model-comparison/high-fidelity-4x/before.webp").arg(execDir)),
            QPixmap(QString("%1/res/upsc/model-comparison/high-fidelity-4x/after.webp").arg(execDir)),
        },
        SUpscSelectModelData{
            3,
            EUpscSmapleType_Remacri,
            "Remacri(Non-Commercial)",
            "For natural images. Added sharpness and detail. No commercial use.",
            QPixmap(QString("%1/res/upsc/model-comparison/remacri-4x/before.webp").arg(execDir)),
            QPixmap(QString("%1/res/upsc/model-comparison/remacri-4x/after.webp").arg(execDir)),
        },
        SUpscSelectModelData{
            4,
            EUpscSmapleType_Ultramix,
            "Ultramix(Non-Commercial)",
            "For natural images with a balance of sharpness and detail.",
            QPixmap(QString("%1/res/upsc/model-comparison/ultramix-balanced-4x/before.webp").arg(execDir)),
            QPixmap(QString("%1/res/upsc/model-comparison/ultramix-balanced-4x/after.webp").arg(execDir)),
        },
        SUpscSelectModelData{
            5,
            EUpscSmapleType_Ultrasharp,
            "Ultrasharp(Non-Commercial)",
            "For natural images with a focus on sharpness.",
            QPixmap(QString("%1/res/upsc/model-comparison/ultrasharp-4x/before.webp").arg(execDir)),
            QPixmap(QString("%1/res/upsc/model-comparison/ultrasharp-4x/after.webp").arg(execDir)),
        },
        SUpscSelectModelData{
            6,
            EUpscSmapleType_Digital,
            "Digital Art",
            "For digital art and illustrations.",
            QPixmap(QString("%1/res/upsc/model-comparison/digital-art-4x/before.webp").arg(execDir)),
            QPixmap(QString("%1/res/upsc/model-comparison/digital-art-4x/after.webp").arg(execDir)),
        },
    };
    return m_pSelectModelDatas;
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