#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class InpaintingRepository : public Repository {
public:
    explicit InpaintingRepository();
    ~InpaintingRepository();
};