#pragma once
#include "inavbarcheckedobserver.h"
#include "funcenum.h"

class INavbarCheckedSubject {
public:
    virtual void navbarCheckedSubjectAttach(INavbarCheckedObserver *observer) = 0;
    virtual void navbarCheckedSubjectDetach(INavbarCheckedObserver *observer) = 0;
    virtual void navbarCheckedNotify(EFunc) = 0;
};