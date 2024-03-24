/*
 * @Author: weick
 * @Date: 2023-12-09 23:52:37
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 10:11:02
 */

#pragma once
#include <QPixmap>
#include <QString>

// 暂不持支：svg ico cur xpm heic jfif heif jif rgf xwd jfi picon
#define CONV_OUT_FORMATS "jpg jpeg webp hdr bmp gif dds psd tiff tga rgb avif pgm jp2 rgba ppm xbm pcx wbmp exr map jbg pnm jpe yuv pbm pdb g4 ras g3 pal sgi pict pfm pcd jps uyvy pgx vips six fts fax jbig ipl sun pam viff mng mtv xv pct sixel palm rgbo hrz otb"

#define COMPRESS_OUT_FORMATS "sameassource jpg png"
#define COMPRESS_OUT_QUALITY "10 20 30 40 50 60 70 80 90"

using ImageFunc = enum {
    STARTUP = 0,
    CONVERSION,    // 图片转换
    COMPRESSION,   // 图片压缩
    EDIT,          // 图片编辑
    AMPLIFICATION, // 图像放大
    MANIPULATION,  // 图片抠像
    ERASE,         // 图片擦除
    ENHANCEMENT,   // 图像增强
    RESTORATION,   // 图像复原
    EFFECT,        // 图片效果
    SPECIALEFFECT  // 图片特效
};

QString ImageFuncEnum2QString(ImageFunc param);

namespace imageconversion {
using Status = enum {
    NONE = 0,
    START,
    FINISHED,
    CANCEL
};

QString StatusEnum2QString(Status param);

struct Data {
    QString file_name = "";
    QString file_path = "";
    Status state = Status::NONE;
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    bool is_checked = false;
};

} // namespace imageconversion

namespace imagecompression {
using Status = enum {
    NONE = 0,
    START,
    FINISHED,
    CANCEL
};

QString StatusEnum2QString(Status param);

struct Data {
    QString file_name = "";
    QString file_path = "";
    Status state = Status::NONE;
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    bool is_checked = false;
};

struct Param {
    int jpeg_quality;
    int png_quality;
    int gif_quality;
    int webp_quality;
    bool keep_metadata;
    bool png_force_zopfli;
    bool optimize;
    int width;
    int height;
};

struct Result {
    bool success;
    char *error_message;
};

} // namespace imagecompression

namespace imageedit {
using Status = enum {
    NONE = 0,
    START,
    FINISHED,
    CANCEL
};

QString StatusEnum2QString(Status param);

struct Data {
    QString file_name = "";
    QString file_path = "";
    Status state = Status::NONE;
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    bool is_checked = false;
};

} // namespace imageedit