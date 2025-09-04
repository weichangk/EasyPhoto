#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class ImgDlRepository : public Repository {
public:
    explicit ImgDlRepository();
    ~ImgDlRepository();
};