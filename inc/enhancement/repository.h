#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class EnhancementRepository : public Repository {
public:
    explicit EnhancementRepository();
    ~EnhancementRepository();
};