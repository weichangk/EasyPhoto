#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class EffectsRepository : public Repository {
public:
    explicit EffectsRepository();
    ~EffectsRepository();
};