#include "erase/repository.h"

#include <QCoreApplication>

EraseRepository::EraseRepository() {
    m_pImportListRepository = new ImportListRepository();
}

EraseRepository::~EraseRepository() {
}

QString EraseRepository::getSampleImage1Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample1.webp").arg(execDir);
}

QString EraseRepository::getSampleImage2Path() {
    QString execDir = QCoreApplication::applicationDirPath();
    return QString("%1/sample2.webp").arg(execDir);
}

ImportListRepository *EraseRepository::getImportListRepository() {
    return m_pImportListRepository;
}