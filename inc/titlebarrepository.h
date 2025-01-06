#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class TitlebarRepository : public Repository {
public:
    explicit TitlebarRepository();
    ~TitlebarRepository();
};