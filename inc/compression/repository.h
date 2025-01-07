#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class CompressionRepository : public Repository {
public:
    explicit CompressionRepository();
    ~CompressionRepository();
};