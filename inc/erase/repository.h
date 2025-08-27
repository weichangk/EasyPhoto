#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "model.h"
#include "import/importlistrepository.h"

using namespace QtmMvp;

class EraseRepository : public Repository {
public:
    explicit EraseRepository();
    ~EraseRepository();

    QString getSampleImage1Path();
    QString getSampleImage2Path();

    ImportListRepository *getImportListRepository();

private:
    ImportListRepository *m_pImportListRepository = nullptr;
};