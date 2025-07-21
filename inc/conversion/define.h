
#pragma once

#include <QRect>

inline QRect convListComboRect(QRect rc) {
    return QRect(rc.right() - 356, rc.center().y() - 12, 70, 24);
}

inline QRect convListCheckedRect(QRect rc) {
    return QRect(rc.x() + 24, rc.y() + 8, 16, 16);
}

inline QRect convListNameRect(QRect rc) {
    QRect checkedRect = convListCheckedRect(rc);
    return QRect(checkedRect.right() + 8, checkedRect.y(), 280, 16);
}

inline QRect convListDelRect(QRect rc) {
    return QRect(rc.right() - 20 - 16, rc.y() + 8, 16, 16);
}

inline QRect convListConvRect(QRect rc) {
    return QRect(rc.right() - 114, rc.center().y() - 10, 70, 20);
}

inline QRect convListResolutionRect(QRect rc) {
    return QRect(rc.right() - 504, rc.center().y() - 8, 80, 16);
}

inline QRect convListStateRect(QRect rc) {
    return QRect(rc.right() - 196, rc.center().y() - 8, 16, 16);
}
