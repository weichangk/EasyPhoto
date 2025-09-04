#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "types.h"
#include "import/importlistrepository.h"

using namespace QtmMvp;

class UpscRepository : public Repository {
public:
    explicit UpscRepository();
    ~UpscRepository();

    QList<SUpscModelData> getModelDatas();

    QString getSampleImage1Path();
    QString getSampleImage2Path();

    ImportListRepository *getImportListRepository();

private:
    ImportListRepository *m_pImportListRepository = nullptr;
};