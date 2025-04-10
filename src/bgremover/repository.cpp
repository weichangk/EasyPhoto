#include "bgremover/repository.h"

BackgroungRemoverRepository::BackgroungRemoverRepository() {
}

BackgroungRemoverRepository::~BackgroungRemoverRepository() {
}

QList<SBGRemoverData> BackgroungRemoverRepository::datas() {
    return m_datas;
}

void BackgroungRemoverRepository::appendData(QList<SBGRemoverData> datas) {
    m_datas.append(datas);
}

void BackgroungRemoverRepository::deleteData(const QStringList filePaths) {
    auto func = [](const SBGRemoverData &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.file_path);
    };
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_datas.end());
}

void BackgroungRemoverRepository::deleteCheckedData() {
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), [](const SBGRemoverData &cd) {
                      return cd.is_checked == true;
                  }),
                  m_datas.end());
}

void BackgroungRemoverRepository::clearData() {
    m_datas.clear();
}

void BackgroungRemoverRepository::switchCheckedData(const QString filePath) {
    auto func = [](const SBGRemoverData &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePath));
    if (it != m_datas.end()) {
        it->is_checked = !it->is_checked;
    }
}

void BackgroungRemoverRepository::checkedAllData(bool checked) {
    for (auto &data : m_datas) {
        data.is_checked = checked;
    }
}