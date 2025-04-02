#pragma once

#include <QString>
#include <QPixmap>

#define ENHANCE_INPUT_FORMATS "png jpg jpeg webp"
#define ENHANCE_OUTPUT_FORMATS "png jpg webp"

struct SEnhanceInputData {
    QString name = "";
    QString path = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
};
Q_DECLARE_METATYPE(SEnhanceInputData)

struct SEnhanceModelData {
    QString id = "";
    QString name = "";
    QString path = "";
    QPixmap thumbnail = QPixmap();
};
Q_DECLARE_METATYPE(SEnhanceModelData)