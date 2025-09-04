#include "crop/repository.h"

#include <QCoreApplication>

CropRepository::CropRepository() {
    m_pImportListRepository = new ImportListRepository();
}

CropRepository::~CropRepository() {
}

QString CropRepository::getSampleImage1Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample1.webp").arg(execDir);
}

QString CropRepository::getSampleImage2Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample2.webp").arg(execDir);
}

ImportListRepository *CropRepository::getImportListRepository() {
    return m_pImportListRepository;
}