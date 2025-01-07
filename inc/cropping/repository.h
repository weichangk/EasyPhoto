#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class CroppingRepository : public Repository {
public:
    explicit CroppingRepository();
    ~CroppingRepository();
};