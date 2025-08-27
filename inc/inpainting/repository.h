#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class InpaintingRepository : public Repository {
public:
    explicit InpaintingRepository();
    ~InpaintingRepository();
};