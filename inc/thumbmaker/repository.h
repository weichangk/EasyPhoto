#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class ThumbnailMakerRepository : public Repository {
public:
    explicit ThumbnailMakerRepository();
    ~ThumbnailMakerRepository();
};