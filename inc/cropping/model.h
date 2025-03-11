#pragma once

#include <QString>
#include <QPixmap>

#define CROP_INPUT_FORMATS "jpg jpeg webp"

struct SCroppingData {
    QString file_name = "";
    QString file_path = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    bool is_checked = false;
};
Q_DECLARE_METATYPE(SCroppingData)