#include "gifmk/repository.h"

GifMkRepository::GifMkRepository() {
}

GifMkRepository::~GifMkRepository() {
}

QList<SGifMkData> GifMkRepository::datas() {
    return m_datas;
}

void GifMkRepository::appendData(QList<SGifMkData> datas) {
    m_datas.append(datas);
}

void GifMkRepository::deleteData(const QStringList filePaths) {
    auto func = [](const SGifMkData &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.file_path);
    };
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_datas.end());
}

void GifMkRepository::deleteCheckedData() {
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), [](const SGifMkData &cd) {
                      return cd.is_checked == true;
                  }),
                  m_datas.end());
}

void GifMkRepository::clearData() {
    m_datas.clear();
}