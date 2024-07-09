/*
 * @Author: weick
 * @Date: 2023-12-09 23:52:37
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 08:04:05
 */

#pragma once
#include <QPixmap>
#include <QString>
#include <QMap>

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
    SPECIALEFFECT,  // 图片特效
    IMAGE2GIF
};

QString ImageFuncEnum2QString(ImageFunc param);

using ImageQuality = enum {
    Low = 0,
    Medium,
    High,
};

using ImageResolution = enum {
    // 标清分辨率（SD，Standard Definition）
    VGA = 0, // 640×480 (VGA)
    NTSC,    // 720×480 (NTSC)
    PAL,     // 720×576 (PAL)

    // 高清分辨率（HD，High Definition）
    _720p, // 1280×720 (720p)
    WXGAHD,  // 1366×768 (WXGA)

    // 全高清分辨率（Full HD）
    _1080p, // 1920×1080 (1080p)

    // 超高清分辨率（UHD，Ultra High Definition）
    _2K, // 2560×1440 (1440p，2K)
    _4K, // 3840×2160 (2160p，4K)
    _5K, // 5120×2880 (5K)
    _8K, // 7680×4320 (4320p，8K)

    // 宽屏分辨率
    WXGA,     // 1280×800 (WXGA)
    WXGAPRO,  // 1440×900 (WXGA+)
    WSXGAPRO, // 1680×1050 (WSXGA+)
    WUXGA,    // 1920×1200 (WUXGA)
    UWHD,     // 2560×1080 (UWHD)
    UWQHD,    // 3440×1440 (UWQHD)
    WQHDPRO,  // 3840×1600 (WQHD+)

    // 移动设备常见分辨率
    iPhone5,         // 1136×640 (iPhone 5/5S/5C, iPhone SE)
    iPhone6,         // 1334×750 (iPhone 6/6S/7/8)
    iPhone6Plus,     // 1920×1080 (iPhone 6 Plus/6S Plus/7 Plus/8 Plus)
    iPhoneX,         // 2436×1125 (iPhone X/XS/11 Pro)
    iPhoneXS,        // 2688×1242 (iPhone XS Max/11 Pro Max)
    iPhone121314,    // 1170×2532 (iPhone 12/13/14)
    iPhone121314Pro, // 1284×2778 (iPhone 12/13/14 Pro Max)
};

static const QMap<ImageResolution, QString> ImageResolutionDesMap = {
    {VGA, "640×480"},
    {NTSC, "720×480"},
    {PAL, "720×576"},
    {_720p, "1280×720"},
    {WXGAHD, "1366×768"},
    {_1080p, "1920×1080"},
    {_2K, "2560×1440"},
    {_4K, "3840×2160"},
    {_5K, "5120×2880"},
    {_8K, "7680×4320"},
    {WXGA, "1280×800"},
    {WXGAPRO, "1440×900"},
    {WSXGAPRO, "1680×1050"},
    {WUXGA, "1920×1200"},
    {UWHD, "2560×1080"},
    {UWQHD, "3440×1440"},
    {WQHDPRO, "3840×1600"},
    {iPhone5, "1136×640"},
    {iPhone6, "1334×750"},
    {iPhone6Plus, "1920×1080"},
    {iPhoneX, "2436×1125"},
    {iPhoneXS, "2688×1242"},
    {iPhone121314, "1170×2532"},
    {iPhone121314Pro, "1284×2778"}
};

static const QMap<ImageResolution, QSize> ImageResolutionSizeMap = {
    {VGA, QSize(640, 480)},
    {NTSC, QSize(720, 480)},
    {PAL, QSize(720, 576)},
    {_720p, QSize(1280, 720)},
    {WXGAHD, QSize(1366, 768)},
    {_1080p, QSize(1920, 1080)},
    {_2K, QSize(2560, 1440)},
    {_4K, QSize(3840, 2160)},
    {_5K, QSize(5120, 2880)},
    {_8K, QSize(7680, 4320)},
    {WXGA, QSize(1280, 800)},
    {WXGAPRO, QSize(1440, 900)},
    {WSXGAPRO, QSize(1680, 1050)},
    {WUXGA, QSize(1920, 1200)},
    {UWHD, QSize(2560, 1080)},
    {UWQHD, QSize(3440, 1440)},
    {WQHDPRO, QSize(3840, 1600)},
    {iPhone5, QSize(1136, 640)},
    {iPhone6, QSize(1334, 750)},
    {iPhone6Plus, QSize(1920, 1080)},
    {iPhoneX, QSize(2436, 1125)},
    {iPhoneXS, QSize(2688, 1242)},
    {iPhone121314, QSize(1170, 2532)},
    {iPhone121314Pro, QSize(1284, 2778)}
};

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
    bool editor_visible = false;
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

namespace image2gif {
using Status = enum {
    NONE = 0,
    START,
    FINISHED,
    CANCEL
};

struct Data {
    QString file_name = "";
    QString file_path = "";
    Status state = Status::NONE;
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap before_add_icon = QPixmap();
    QPixmap after_add_icon = QPixmap();
};

struct Param {
    int fps;
    ImageQuality quality;
    ImageResolution resolution;
    int width;
    int height;
    bool loop;
};
} // namespace image2gif

namespace imageerase {
using Status = enum {
    NONE = 0,
    START,
    FINISHED,
    CANCEL
};

struct Data {
    QString file_name = "";
    QString file_path = "";
    Status state = Status::NONE;
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
};
} // namespace imageerase

namespace imageenhancement {
using Status = enum {
    NONE = 0,
    START,
    FINISHED,
    CANCEL
};

struct Data {
    QString file_name = "";
    QString file_path = "";
    Status state = Status::NONE;
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
};
} // namespace imageenhancement