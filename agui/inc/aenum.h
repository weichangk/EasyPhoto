#pragma once
#include "agui_global.h"

class AGUI_EXPORT AEnum : public QObject
{
    Q_OBJECT
public:
    AEnum(){}
    enum StyleStatus
    {
        Normal = 0,
        Hover,
        Pressed,
        Checked,
        Disabled
    };
    Q_ENUM(StyleStatus)
};
