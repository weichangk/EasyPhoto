#pragma once
#include "ifuncchangeobserver.h"
#include "funcenum.h"

class IFuncChangeSubject {
public:
    virtual void attach(IFuncChangeObserver *observer) = 0;
    virtual void detach(IFuncChangeObserver *observer) = 0;
    virtual void notifyFuncChange(EFunc) = 0;
};