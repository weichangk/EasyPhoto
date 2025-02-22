#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class MyFileRepository : public Repository {
public:
    explicit MyFileRepository();
    ~MyFileRepository();
};