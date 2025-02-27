#pragma once
#include "funcenum.h"

class INavbarCheckedObserver {
public:
    virtual void navbarChecked(EFunc) = 0;
};