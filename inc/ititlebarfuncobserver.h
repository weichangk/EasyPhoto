#pragma once
#include "titlebarenum.h"

class ITitlebarFuncObserver {
public:
    virtual void titleBarFuncHandle(ETitleBarFunc) = 0;
};