#pragma once
#include "funcenum.h"

class IFuncChangeObserver {
public:
    virtual void funcChangeHandle(EFunc) = 0;
};