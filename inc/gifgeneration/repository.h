#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "model.h"

using namespace qtmaterialmvp;

class GifGenerationRepository : public Repository {
    public:
        explicit GifGenerationRepository();
        ~GifGenerationRepository();
        QList<SGifGenerationData> datas();
        void appendData(QList<SGifGenerationData> datas);
        void deleteData(const QStringList filePaths);
        void deleteCheckedData();
        void clearData();
    
    private:
        QList<SGifGenerationData> m_datas;
    };