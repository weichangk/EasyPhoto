#pragma once
#include "funcenum.h"

class IFuncChangeObserver {
public:
    virtual void funcChange(EFunc) = 0;
};