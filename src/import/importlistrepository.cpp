#include "import/importlistrepository.h"

ImportListRepository::ImportListRepository() {
}

ImportListRepository::~ImportListRepository() {
}

QList<SImportListItem> ImportListRepository::getDatas() {
    return m_pDatas;
}

void ImportListRepository::appendData(QList<SImportListItem> datas) {
    m_pDatas.append(datas);
}

void ImportListRepository::deleteData(const QStringList filePaths) {
    auto func = [](const SImportListItem &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.path);
    };
    m_pDatas.erase(std::remove_if(m_pDatas.begin(), m_pDatas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_pDatas.end());
}

void ImportListRepository::clearData() {
    m_pDatas.clear();
}