#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "types.h"
#include "import/importlistrepository.h"

using namespace QtmMvp;

class GifMkRepository : public Repository {
    public:
        explicit GifMkRepository();
        ~GifMkRepository();
        
        ImportListRepository *getImportListRepository();

    private:
        QList<SGifMkData> m_datas;
        ImportListRepository *m_pImportListRepository = nullptr;
    };