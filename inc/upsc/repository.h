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

    QString getSampleImagePath(EUpscSmapleType type);

    ImportListRepository *getImportListRepository();

private:
    ImportListRepository *m_pImportListRepository = nullptr;
};