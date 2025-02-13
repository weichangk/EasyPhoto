#include "gifgeneration/repository.h"

GifGenerationRepository::GifGenerationRepository() {
}

GifGenerationRepository::~GifGenerationRepository() {
}

QList<SGifGenerationData> GifGenerationRepository::datas() {
    return m_datas;
}

void GifGenerationRepository::appendData(QList<SGifGenerationData> datas) {
    m_datas.append(datas);
}

void GifGenerationRepository::deleteData(const QStringList filePaths) {
    auto func = [](const SGifGenerationData &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.file_path);
    };
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_datas.end());
}

void GifGenerationRepository::deleteCheckedData() {
    m_datas.erase(std::remove_if(m_datas.begin(), m_datas.end(), [](const SGifGenerationData &cd) {
                      return cd.is_checked == true;
                  }),
                  m_datas.end());
}

void GifGenerationRepository::clearData() {
    m_datas.clear();
}