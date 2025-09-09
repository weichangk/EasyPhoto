#pragma once
#include "globalpresenter.h"
#include "types.h"
#include "mvp/repository.h"
#include "import/importlistrepository.h"

using namespace QtmMvp;

class BgRmRepository : public Repository {
public:
    explicit BgRmRepository();
    ~BgRmRepository();

    QString getSampleImage1Path();
    QString getSampleImage2Path();

    ImportListRepository *getImportListRepository();

private:
    ImportListRepository *m_pImportListRepository = nullptr;
};