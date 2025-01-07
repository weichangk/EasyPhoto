#include "mainrepository.h"

MainRepository::MainRepository() {
    m_pTitlebarRepository = new TitlebarRepository();
    m_pNavbarRepository = new NavbarRepository();
    m_pFuncAreaRepository = new FuncAreaRepository();
}

MainRepository::~MainRepository() {
}

TitlebarRepository *MainRepository::titlebarRepository() const {
    return m_pTitlebarRepository;
}

NavbarRepository *MainRepository::navbarRepository() const {
    return m_pNavbarRepository;
}

FuncAreaRepository *MainRepository::funcAreaRepository() const {
    return m_pFuncAreaRepository;
}