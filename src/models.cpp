/*
 * @Author: weick
 * @Date: 2024-03-24 10:06:40
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 08:05:39
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
    case ImageFunc::IMAGE2GIF:
        return "IMAGE2GIF";
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
    return QRect(rect.x() / ratio, rect.y() / ratio, rect.width() / ratio, rect.height() / ratio);
}

QRect PreviewRect2CropRect(QRect rect, double ratio) {
    return QRect(rect.x() * ratio, rect.y() * ratio, rect.width() * ratio, rect.height() * ratio);
}

}