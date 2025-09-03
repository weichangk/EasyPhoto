#pragma once

#include <QString>
#include <QPixmap>

#define GIFGENERATION_INPUT_FORMATS "jpg jpeg png bmp"
#define GIFGENERATION_OUTPUT_MINFRAMERATE 1
#define GIFGENERATION_OUTPUT_MAXFRAMERATE 60
#define GIFMKSCALE "original 16:9 1:1"
struct SGifMkData {
    QString file_name = "";
    QString file_path = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    bool is_checked = false;
};
Q_DECLARE_METATYPE(SGifMkData)