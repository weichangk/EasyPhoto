#include "import/importlistrepository.h"

ImportListRepository::ImportListRepository() {
}

ImportListRepository::~ImportListRepository() {
}

QList<SImageData> ImportListRepository::getDatas() {
    return m_pDatas;
}

void ImportListRepository::appendData(QList<SImageData> datas) {
    m_pDatas.append(datas);
}

void ImportListRepository::deleteData(const QStringList filePaths) {
    auto func = [](const SImageData &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.file_path);
    };
    m_pDatas.erase(std::remove_if(m_pDatas.begin(), m_pDatas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_pDatas.end());
}

void ImportListRepository::clearData() {
    m_pDatas.clear();
}

int ImportListRepository::getDataIndex(const QString filePath) {
    int index = -1;
    bool match = false;
    foreach (const SImageData &item, m_pDatas) {
        index += 1;
        if (item.file_path == filePath) {
            match = true;
            return index;
        }
    }
    if (!match) {
        index = -1;
    }
    return index;
}