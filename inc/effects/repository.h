#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class EffectsRepository : public Repository {
public:
    explicit EffectsRepository();
    ~EffectsRepository();
};