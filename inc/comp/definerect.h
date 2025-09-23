
#pragma once

#include <QRect>

inline QRect compListSizeRect(QRect rc) {
    return QRect(rc.right() - 356 - 50, rc.center().y() - 12, 140, 24);
}

inline QRect compListCheckedRect(QRect rc) {
    return QRect(rc.x() + 24, rc.center().y() - 6, 12, 12);
}

inline QRect compListNameRect(QRect rc) {
    QRect checkedRect = compListCheckedRect(rc);
    return QRect(checkedRect.right() + 8, rc.center().y() - 8, 280, 16);
}

inline QRect compListDelRect(QRect rc) {
    return QRect(rc.right() - 20 - 16, rc.y() + 8, 16, 16);
}

inline QRect compListConvRect(QRect rc) {
    return QRect(rc.right() - 114, rc.center().y() - 10, 70, 20);
}

inline QRect compListResolutionRect(QRect rc) {
    return QRect(rc.right() - 504, rc.center().y() - 8, 80, 16);
}

inline QRect compListStateRect(QRect rc) {
    return QRect(rc.right() - 196, rc.center().y() - 8, 16, 16);
}
