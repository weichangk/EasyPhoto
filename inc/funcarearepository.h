#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class FuncAreaRepository : public Repository {
public:
    explicit FuncAreaRepository();
    ~FuncAreaRepository();
};