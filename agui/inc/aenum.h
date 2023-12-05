/*
 * @Author: weick
 * @Date: 2023-12-05 22:51:36
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:51:36
 */

#pragma once
#include "agui_global.h"

class AGUI_EXPORT AEnum : public QObject {
    Q_OBJECT
public:
    AEnum() {
    }
    enum StyleStatus {
        Normal = 0,
        Hover,
        Pressed,
        Checked,
        Disabled
    };
    Q_ENUM(StyleStatus)
};
