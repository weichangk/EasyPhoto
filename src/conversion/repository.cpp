#include "conversion/repository.h"

ConversionRepository::ConversionRepository() {
}

ConversionRepository::~ConversionRepository() {
}

QList<SConversionData> ConversionRepository::datas() {
    return m_datas;
}

void ConversionRepository::updateData(const SConversionData &data) {
    auto func = [](const SConversionData &cd, const QString &filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, data.file_path));
    if (it != m_datas.end()) {
        *it = data;
    } else {
        m_datas.append(data);
    }
}

void ConversionRepository::updateData(const QString filePath, const SConversionData &data) {
    auto func = [](const SConversionData &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePath));
    if (it != m_datas.end()) {
        *it = data;
    }
}

void ConversionRepository::appendData(QList<SConversionData> datas) {
    m_datas.append(datas);
}

void ConversionRepository::deleteData(const QStringList filePaths) {
    auto func = [](const SConversionData &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.file_path);
    };
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_datas.end());
}

void ConversionRepository::deleteCheckedData() {
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), [](const SConversionData &cd) {
                      return cd.is_checked == true;
                  }),
                  m_datas.end());
}

void ConversionRepository::clearData() {
    m_datas.clear();
}

void ConversionRepository::switchCheckedData(const QString filePath) {
    auto func = [](const SConversionData &cd, QString filePath) {
        return cd.file_path == filePath;
    };
    auto it = std::find_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePath));
    if (it != m_datas.end()) {
        it->is_checked = !it->is_checked;
    }
}

void ConversionRepository::checkedAllData(bool checked) {
    for (auto &data : m_datas) {
        data.is_checked = checked;
    }
}