#include "bgrm/repository.h"

BgRmRepository::BgRmRepository() {
}

BgRmRepository::~BgRmRepository() {
}

QList<SBgRmData> BgRmRepository::datas() {
    return m_datas;
}

void BgRmRepository::appendData(QList<SBgRmData> datas) {
    m_datas.append(datas);
}

void BgRmRepository::deleteData(const QStringList filePaths) {
    auto func = [](const SBgRmData &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.file_path);
    };
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_datas.end());
}

void BgRmRepository::deleteCheckedData() {
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), [](const SBgRmData &cd) {
                      return cd.is_checked == true;
                  }),
                  m_datas.end());
}

void BgRmRepository::clearData() {
    m_datas.clear();
}

void BgRmRepository::switchCheckedData(const QString filePath) {
    auto func = [](const SBgRmData &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePath));
    if (it != m_datas.end()) {
        it->is_checked = !it->is_checked;
    }
}

void BgRmRepository::checkedAllData(bool checked) {
    for (auto &data : m_datas) {
        data.is_checked = checked;
    }
}