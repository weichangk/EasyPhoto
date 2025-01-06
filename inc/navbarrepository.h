#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class NavbarRepository : public Repository {
public:
    explicit NavbarRepository();
    ~NavbarRepository();
};