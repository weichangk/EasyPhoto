#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class MyFileRepository : public Repository {
public:
    explicit MyFileRepository();
    ~MyFileRepository();
};