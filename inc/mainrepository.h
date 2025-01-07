#pragma once
#include "globalpresenter.h"
#include "titlebarrepository.h"
#include "navbarrepository.h"
#include "funcarearepository.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class MainRepository : public Repository {
public:
    explicit MainRepository();
    ~MainRepository();

    TitlebarRepository *titlebarRepository() const;
    NavbarRepository *navbarRepository() const;
    FuncAreaRepository *funcAreaRepository() const;

private:
    TitlebarRepository *m_pTitlebarRepository = nullptr;
    NavbarRepository *m_pNavbarRepository = nullptr;
    FuncAreaRepository *m_pFuncAreaRepository = nullptr;
};