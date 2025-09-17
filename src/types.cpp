#include "types.h"

QStringList UpscOutputFormats() {
    QString format = UPSC_OUTPUT_FORMATS;
    QStringList formats = format.split(';');
    return formats;
}