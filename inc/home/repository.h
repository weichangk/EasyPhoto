#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class HomeRepository : public Repository {
public:
    explicit HomeRepository();
    ~HomeRepository();
};