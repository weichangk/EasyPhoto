#pragma once
#include "ititlebarfuncobserver.h"
#include "titlebarenum.h"

class ITitlebarFuncSubject {
public:
    virtual void titlebarFuncSubjectAttach(ITitlebarFuncObserver *observer) = 0;
    virtual void titlebarFuncSubjectDetach(ITitlebarFuncObserver *observer) = 0;
    virtual void titlebarFuncSubjectNotify(ETitleBarFunc) = 0;
};