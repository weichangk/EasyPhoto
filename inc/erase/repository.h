#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class EraseRepository : public Repository {
public:
    explicit EraseRepository();
    ~EraseRepository();
};