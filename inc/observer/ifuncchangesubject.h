#pragma once
#include "ifuncchangeobserver.h"
#include "funcenum.h"

class IFuncChangeSubject {
public:
    virtual void funcChangeSubjectAttach(IFuncChangeObserver *observer) = 0;
    virtual void funcChangeSubjectDetach(IFuncChangeObserver *observer) = 0;
    virtual void funcChangeSubjectNotify(EFunc) = 0;
};