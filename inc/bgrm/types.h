#pragma once

#include <QString>
#include <QPixmap>

#define BGREMOVER_INPUT_FORMATS "png jpg jpeg bmp"

struct SBgRmData {
    QString file_name = "";
    QString file_path = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    bool is_checked = false;
};
Q_DECLARE_METATYPE(SBgRmData)