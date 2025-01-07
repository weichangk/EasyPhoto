#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class ConversionRepository : public Repository {
public:
    explicit ConversionRepository();
    ~ConversionRepository();
};