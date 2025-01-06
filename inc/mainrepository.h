#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class MainRepository : public Repository {
public:
    explicit MainRepository();
    ~MainRepository();
};