#pragma once
#include "navbarobserver.h"
#include "funcenum.h"

class INavbarSubject {
public:
    virtual void attach(INavbarObserver *observer) = 0;
    virtual void detach(INavbarObserver *observer) = 0;
    virtual void notifyNavChange(EFunc) = 0;
};