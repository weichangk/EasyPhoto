#include "bgrm/repository.h"

#include <QCoreApplication>

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

ImportListRepository *BgRmRepository::getImportListRepository() {
    return m_pImportListRepository;
}