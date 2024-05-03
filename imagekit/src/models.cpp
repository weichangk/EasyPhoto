/*
 * @Author: weick
 * @Date: 2024-03-24 10:06:40
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 10:11:32
 */

#include "inc/models.h"

QString ImageFuncEnum2QString(ImageFunc param) {
    switch (param) {
    case ImageFunc::STARTUP:
        return "STARTUP";
    case ImageFunc::CONVERSION:
        return "CONVERSION";
    case ImageFunc::COMPRESSION:
        return "COMPRESSION";
    case ImageFunc::EDIT:
        return "EDIT";
    default:
        return "UNKNOWN";
    }
}

namespace imageconversion {
QString StatusEnum2QString(Status param) {
    switch (param) {
    case Status::NONE:
        return "NONE";
    case Status::START:
        return "START";
    case Status::FINISHED:
        return "FINISHED";
    case Status::CANCEL:
        return "CANCEL";
    default:
        return "UNKNOWN";
    }
}
}

namespace imagecompression {
QString StatusEnum2QString(Status param) {
    switch (param) {
    case Status::NONE:
        return "NONE";
    case Status::START:
        return "START";
    case Status::FINISHED:
        return "FINISHED";
    case Status::CANCEL:
        return "CANCEL";
    default:
        return "UNKNOWN";
    }
}
}

namespace imageedit {
QString StatusEnum2QString(Status param) {
    switch (param) {
    case Status::NONE:
        return "NONE";
    case Status::START:
        return "START";
    case Status::FINISHED:
        return "FINISHED";
    case Status::CANCEL:
        return "CANCEL";
    default:
        return "UNKNOWN";
    }
}

QRect CropRect2PreviewRect(QRect rect, double ratio) {
    int width = rect.width();
    int height = rect.height();
    return QRect(0, 0, width / ratio, height / ratio);
}

QRect PreviewRect2CropRect(QRect rect, double ratio) {
    int width = rect.width();
    int height = rect.height();
    return QRect(0, 0, width * ratio, height * ratio);
}

}