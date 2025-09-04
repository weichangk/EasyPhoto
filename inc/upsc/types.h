#pragma once

#include <QString>
#include <QPixmap>

#define ENHANCE_INPUT_FORMATS "png jpg jpeg webp"
#define ENHANCE_OUTPUT_FORMATS "png jpg webp"

struct SUpscModelData {
    QString id = "";
    QString name = "";
    QString path = "";
    QPixmap thumbnail = QPixmap();
};
Q_DECLARE_METATYPE(SUpscModelData)