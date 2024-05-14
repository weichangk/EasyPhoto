/*
 * @Author: weick
 * @Date: 2023-12-09 23:52:37
 * @Last Modified by: weick
 * @Last Modified time: 2024-05-11 08:05:24
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
static const int kCropRectMinW = 100;
static const int kCropRectMinH = 100;
static const int kRotateAngleDefaultValue = 0;
static const int kLuminanceRangeMin = -100;
static const int kContrastRangeMin = -100;
static const int kSaturationRangeMin = -100;
static const int kLuminanceRangeMax = 100;
static const int kContrastRangeMax = 100;
static const int kSaturationRangeMax = 100;
static const int kLuminanceDefaultValue = 0;
static const int kContrastDefaultValue = 0;
static const int kSaturationDefaultValue = 0;
static const int kPictureAlphaRangeMin = 0;
static const int kPictureAlphaRangeMax = 100;
static const int kPictureAlphaRangeDefault = 0;
static const int kImageWatermarkSettingItemWidth = 100;
static const int kImageWatermarkSettingItemHeight = 80;
static const int kImageWatermarkSettingItemSpacing = 4;
static const int kTextWatermarkSettingItemEditWidth = 200;
static const int kTextWatermarkSettingItemWidth = 260;
static const int kTextWatermarkSettingItemHeight = 32;
static const int kTextWatermarkSettingItemSpacing = 4;
using Status = enum {
    NONE = 0,
    START,
    FINISHED,
    CANCEL
};

QString StatusEnum2QString(Status param);

struct ImageWatermarkData {
    QString file_path = "";
    QRect geometry;
    int alpha;
};

struct ImageWatermarkSettingData {
    QString file_path = "";
    QString file_name = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
};

struct TextWatermarkData {
    QString text = "";
    QRect geometry;
};

struct TextWatermarkSettingData {
    QString id = "";
    QString text = "";
    QPixmap delete_icon = QPixmap();
};

struct Data {
    QString file_name = "";
    QString file_path = "";
    Status state = Status::NONE;
    QPixmap delete_icon = QPixmap();
    double preview_ratio = 0;
    double aspect_ratio = 0;
    QRect crop_rect;
    QRect origin_crop_rect;
    bool is_equal_ratio_crop_ = false;
    int rotate_angle = 0;
    int luminance = 0;
    int contrast = 0;
    int saturation = 0;
    QList<ImageWatermarkData> image_watermark_datas;
    QList<TextWatermarkData> text_watermark_datas;
};

QRect CropRect2PreviewRect(QRect rect, double ratio);
QRect PreviewRect2CropRect(QRect rect, double ratio);

} // namespace imageedit