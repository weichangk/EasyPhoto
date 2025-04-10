#include "cropping/repository.h"

#include <QCoreApplication>

CroppingRepository::CroppingRepository() {
    m_pImportListRepository = new ImportListRepository();
}

CroppingRepository::~CroppingRepository() {
}

QString CroppingRepository::getSampleImage1Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample1.webp").arg(execDir);
}

QString CroppingRepository::getSampleImage2Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample2.webp").arg(execDir);
}

ImportListRepository *CroppingRepository::getImportListRepository() {
    return m_pImportListRepository;
}