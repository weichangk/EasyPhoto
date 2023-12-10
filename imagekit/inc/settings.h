/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:19
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-09 23:46:14
 */

#pragma once

namespace Default {
static constexpr bool autoStart = false;
}

namespace Limits {
static constexpr int zoomMax = 5;
}

class Settings {
public:
    Settings();

    void load();
    void save();

    bool autoStart() const {
        return m_AutoStart;
    }
    void setAutoStart(bool autoStart) {
        m_AutoStart = autoStart;
    }

private:
    bool m_AutoStart;
};
