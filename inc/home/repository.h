#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "model.h"

using namespace qtmaterialmvp;

class HomeRepository : public Repository {
public:
    explicit HomeRepository();
    ~HomeRepository();

    QList<SFuncItemData> datas();
};