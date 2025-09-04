#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class ThumbMkRepository : public Repository {
public:
    explicit ThumbMkRepository();
    ~ThumbMkRepository();
};