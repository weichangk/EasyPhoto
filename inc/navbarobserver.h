#pragma once
#include "funcenum.h"

class INavbarObserver {
public:
    virtual void navChange(EFunc) = 0;
};