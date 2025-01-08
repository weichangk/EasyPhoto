#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class GifGenerationRepository : public Repository {
public:
    explicit GifGenerationRepository();
    ~GifGenerationRepository();
};