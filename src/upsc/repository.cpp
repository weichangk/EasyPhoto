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
            EUpscModelType_Standard,
            UPSC_MODEL_NAMES[EUpscModelType_Standard],
            UPSC_MODEL_TITLES[EUpscModelType_Standard],
            UPSC_MODEL_DESCS[EUpscModelType_Standard],
            QPixmap(QString("%1/res/upsc/model-comparison/%2/before.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Standard])),
            QPixmap(QString("%1/res/upsc/model-comparison/%2/after.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Standard])),
        },
        SUpscSelectModelData{
            EUpscModelType_Lite,
            UPSC_MODEL_NAMES[EUpscModelType_Lite],
            UPSC_MODEL_TITLES[EUpscModelType_Lite],
            UPSC_MODEL_DESCS[EUpscModelType_Lite],
            QPixmap(QString("%1/res/upsc/model-comparison/%2/before.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Lite])),
            QPixmap(QString("%1/res/upsc/model-comparison/%2/after.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Lite])),
        },
        SUpscSelectModelData{
            EUpscModelType_Fidelity,
            UPSC_MODEL_NAMES[EUpscModelType_Fidelity],
            UPSC_MODEL_TITLES[EUpscModelType_Fidelity],
            UPSC_MODEL_DESCS[EUpscModelType_Fidelity],
            QPixmap(QString("%1/res/upsc/model-comparison/%2/before.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Fidelity])),
            QPixmap(QString("%1/res/upsc/model-comparison/%2/after.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Fidelity])),
        },
        SUpscSelectModelData{
            EUpscModelType_Remacri,
            UPSC_MODEL_NAMES[EUpscModelType_Remacri],
            UPSC_MODEL_TITLES[EUpscModelType_Remacri],
            UPSC_MODEL_DESCS[EUpscModelType_Remacri],
            QPixmap(QString("%1/res/upsc/model-comparison/%2/before.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Remacri])),
            QPixmap(QString("%1/res/upsc/model-comparison/%2/after.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Remacri])),
        },
        SUpscSelectModelData{
            EUpscModelType_Ultramix,
            UPSC_MODEL_NAMES[EUpscModelType_Ultramix],
            UPSC_MODEL_TITLES[EUpscModelType_Ultramix],
            UPSC_MODEL_DESCS[EUpscModelType_Ultramix],
            QPixmap(QString("%1/res/upsc/model-comparison/%2/before.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Ultramix])),
            QPixmap(QString("%1/res/upsc/model-comparison/%2/after.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Ultramix])),
        },
        SUpscSelectModelData{
            EUpscModelType_Ultrasharp,
            UPSC_MODEL_NAMES[EUpscModelType_Ultrasharp],
            UPSC_MODEL_TITLES[EUpscModelType_Ultrasharp],
            UPSC_MODEL_DESCS[EUpscModelType_Ultrasharp],
            QPixmap(QString("%1/res/upsc/model-comparison/%2/before.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Ultrasharp])),
            QPixmap(QString("%1/res/upsc/model-comparison/%2/after.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Ultrasharp])),
        },
        SUpscSelectModelData{
            EUpscModelType_Digital,
            UPSC_MODEL_NAMES[EUpscModelType_Digital],
            UPSC_MODEL_TITLES[EUpscModelType_Digital],
            UPSC_MODEL_DESCS[EUpscModelType_Digital],
            QPixmap(QString("%1/res/upsc/model-comparison/digital-art-4x/before.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Digital])),
            QPixmap(QString("%1/res/upsc/model-comparison/digital-art-4x/after.webp").arg(execDir).arg(UPSC_MODEL_NAMES[EUpscModelType_Digital])),
        },
    };
    return m_pSelectModelDatas;
}

QString UpscRepository::getSampleBeforeImagePath(EUpscModelType type) {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/res/upsc/model-comparison/%2/before.webp").arg(execDir).arg(UPSC_MODEL_NAMES[type]);
}

ImportListRepository *UpscRepository::getImportListRepository() {
    return m_pImportListRepository;
}