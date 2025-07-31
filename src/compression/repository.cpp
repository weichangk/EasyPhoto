#include "compression/repository.h"

CompressionRepository::CompressionRepository() {
}

CompressionRepository::~CompressionRepository() {
}

QList<SCompressionData> CompressionRepository::datas() {
    return m_datas;
}

void CompressionRepository::updateData(const SCompressionData &data) {
    auto func = [](const SCompressionData &cd, const QString &filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, data.file_path));
    if (it != m_datas.end()) {
        *it = data;
    } else {
        m_datas.append(data);
    }
}

void CompressionRepository::updateData(const QString filePath, const SCompressionData &data) {
    auto func = [](const SCompressionData &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePath));
    if (it != m_datas.end()) {
        *it = data;
    }
}

void CompressionRepository::appendData(QList<SCompressionData> datas) {
    m_datas.append(datas);
}

void CompressionRepository::deleteData(const QStringList filePaths) {
    auto func = [](const SCompressionData &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.file_path);
    };
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_datas.end());
}

void CompressionRepository::deleteCheckedData() {
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), [](const SCompressionData &cd) {
                      return cd.is_checked == true;
                  }),
                  m_datas.end());
}

void CompressionRepository::clearData() {
    m_datas.clear();
}

void CompressionRepository::switchCheckedData(const QString filePath) {
    auto func = [](const SCompressionData &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePath));
    if (it != m_datas.end()) {
        it->is_checked = !it->is_checked;
    }
}

void CompressionRepository::checkedAllData(bool checked) {
    for (auto &data : m_datas) {
        data.is_checked = checked;
    }
}