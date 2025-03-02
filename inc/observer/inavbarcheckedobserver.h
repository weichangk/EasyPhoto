#pragma once
#include "funcenum.h"

class INavbarCheckedObserver {
public:
    virtual void navbarCheckedHandle(EFunc) = 0;
};