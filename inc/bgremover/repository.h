#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class BackgroungRemoverRepository : public Repository {
public:
    explicit BackgroungRemoverRepository();
    ~BackgroungRemoverRepository();
};