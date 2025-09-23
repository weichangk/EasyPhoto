#include "comp/repository.h"

CompRepository::CompRepository() {
}

CompRepository::~CompRepository() {
}

QList<SImageData> CompRepository::datas() {
    return m_datas;
}

void CompRepository::updateData(const SImageData &data) {
    auto func = [](const SImageData &cd, const QString &filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, data.file_path));
    if (it != m_datas.end()) {
        *it = data;
    } else {
        m_datas.append(data);
    }
}

void CompRepository::updateData(const QString filePath, const SImageData &data) {
    auto func = [](const SImageData &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePath));
    if (it != m_datas.end()) {
        *it = data;
    }
}

void CompRepository::appendData(QList<SImageData> datas) {
    m_datas.append(datas);
}

void CompRepository::deleteData(const QStringList filePaths) {
    auto func = [](const SImageData &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.file_path);
    };
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_datas.end());
}

void CompRepository::deleteCheckedData() {
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), [](const SImageData &cd) {
                      return cd.is_checked == true;
                  }),
                  m_datas.end());
}

void CompRepository::clearData() {
    m_datas.clear();
}

void CompRepository::switchCheckedData(const QString filePath) {
    auto func = [](const SImageData &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePath));
    if (it != m_datas.end()) {
        it->is_checked = !it->is_checked;
    }
}

void CompRepository::checkedAllData(bool checked) {
    for (auto &data : m_datas) {
        data.is_checked = checked;
    }
}