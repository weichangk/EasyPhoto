#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "types.h"

using namespace QtmMvp;

class GifMkRepository : public Repository {
    public:
        explicit GifMkRepository();
        ~GifMkRepository();
        QList<SGifMkData> datas();
        void appendData(QList<SGifMkData> datas);
        void deleteData(const QStringList filePaths);
        void deleteCheckedData();
        void clearData();
    
    private:
        QList<SGifMkData> m_datas;
    };