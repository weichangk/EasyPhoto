#pragma once

#include "settings.h"

#include <QString>
#include <QPixmap>

// 暂不持支：svg ico cur xpm heic jfif heif jif rgf xwd jfi picon
#define CONV_INPUT_FORMATS "jpg jpeg webp hdr bmp gif dds psd tiff tga rgb avif pgm jp2 rgba ppm xbm pcx wbmp exr map jbg pnm jpe yuv pbm pdb g4 ras g3 pal sgi pict pfm pcd jps uyvy pgx vips six fts fax jbig ipl sun pam viff mng mtv xv pct sixel palm rgbo hrz otb"
#define CONV_OUTPUT_FORMATS "jpg png svg webp avif bmp ico tiff psd eps xbm"

enum EConvState {
    EConvState_Waiting = 0,
    EConvState_Loading,
    EConvState_Success,
    EConvState_Fail,
};

struct SConversionData {
    QString file_name = "";
    QString file_path = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    QMap<EConvState, QPixmap> state_icons;
    bool is_checked = false;
    QSize resolution = QSize(0, 0);
    QString output_format = Default::Conv::outFormat;
    EConvState state = EConvState_Waiting;
};
Q_DECLARE_METATYPE(SConversionData)

struct SConversionOuputFormat {
    QString name = "";
    QString des = "";
    QPixmap icon = QPixmap();
    bool checked = false;
};
Q_DECLARE_METATYPE(SConversionOuputFormat)

#define COMP_INPUT_FORMATS "(*.jpg;*.jpeg;*.png;*.gif;*.webp;*.JPG;*.JPEG;*.PNG;*.GIF;*.WEBP)"
#define COMP_OUT_FORMATS "sameassource jpg png"
#define COMP_OUT_QUALITY "10 20 30 40 50 60 70 80 90"

enum ECompreState {
    ECompreState_Waiting = 0,
    ECompreState_Loading,
    ECompreState_Success,
    ECompreState_Fail,
};


struct SCompressionData {
    QString file_name = "";
    QString file_path = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    QMap<ECompreState, QPixmap> state_icons;
    bool is_checked = false;
    QSize resolution = QSize(0, 0);
    QString output_format = Default::Cmp::outFormat;
    QString intput_size = "";
    QString output_size = "";
    ECompreState state = ECompreState_Waiting;
};
Q_DECLARE_METATYPE(SCompressionData)

struct SCompressionOuputFormat {
    QString name = "";
    QString des = "";
    QPixmap icon = QPixmap();
    bool checked = false;
};
Q_DECLARE_METATYPE(SCompressionOuputFormat)


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

struct SBgImgData {
    QString file_name = "";
    QString file_path = "";
    QPixmap thumbnail = QPixmap();
    bool is_checked = false;
};
Q_DECLARE_METATYPE(SBgImgData)

enum EBgImgType {
    EBgImgType_Custom = 0,
    EBgImgType_General,
    EBgImgType_Scene
};

#define CROP_INPUT_FORMATS "jpg jpeg webp"
#define ERASE_INPUT_FORMATS "png jpg jpeg webp bmp"

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

enum ECropScaleType {
    ECropScaleType_Original = 0,
    ECropScaleType_Custom,
    ECropScaleType_1_1,
    ECropScaleType_16_9,
    ECropScaleType_9_16,
    ECropScaleType_4_3,
    ECropScaleType_3_2,
    ECropScaleType_2_3,
};

struct SCropScaleData {
    ECropScaleType type = ECropScaleType_Original;
    QString name = "Original";
    QPixmap thumbnail = QPixmap();
};
Q_DECLARE_METATYPE(SCropScaleData)

// Upsc
#define UPSC_INPUT_FORMATS "(*.png;*.jpg;*.jpeg;*.jfif;*.webp;*.PNG;*.JPG;*.JPEG;*.JFIF;*.WEBP)"
const QMap<QString, QString> UPSC_OUTPUT_FORMATS{
    {"png", "PNG"},
    {"jpg", "JPG"},
    {"webp", "WEBP"},
};
const QMap<int, QString> UPSC_SCALES{
    {1, "1x"},
    {2, "2x"},
    {3, "3x"},
    {4, "4x"},
    {5, "5x"},
    {6, "6x"},
    {7, "7x"},
    {8, "8x"},
    {9, "9x"},
    {10, "10x"},
    {11, "11x"},
    {12, "12x"},
    {13, "13x"},
    {14, "14x"},
    {15, "15x"},
    {16, "16x"},
};

enum EUpscModelType {
    EUpscModelType_Standard = 0,
    EUpscModelType_Lite,
    EUpscModelType_Fidelity,
    EUpscModelType_Remacri,
    EUpscModelType_Ultramix,
    EUpscModelType_Ultrasharp,
    EUpscModelType_Digital,
};

const QMap<EUpscModelType, QString> UPSC_MODEL_NAMES{
    {EUpscModelType_Standard, "upscayl-standard-4x"},
    {EUpscModelType_Lite, "upscayl-lite-4x"},
    {EUpscModelType_Fidelity, "high-fidelity-4x"},
    {EUpscModelType_Remacri, "remacri-4x"},
    {EUpscModelType_Ultramix, "ultramix-balanced-4x"},
    {EUpscModelType_Ultrasharp, "ultrasharp-4x"},
    {EUpscModelType_Digital, "digital-art-4x"},
};

const QMap<EUpscModelType, QString> UPSC_MODEL_TITLES{
    {EUpscModelType_Standard, "Upscayl Standard"},
    {EUpscModelType_Lite, "Upscayl Life"},
    {EUpscModelType_Fidelity, "High Fidelity"},
    {EUpscModelType_Remacri, "Remacri(Non-Commercial)"},
    {EUpscModelType_Ultramix, "Ultramix(Non-Commercial)"},
    {EUpscModelType_Ultrasharp, "Ultrasharp(Non-Commercial)"},
    {EUpscModelType_Digital, "Digital Art"},
};

const QMap<EUpscModelType, QString> UPSC_MODEL_DESCS{
    {EUpscModelType_Standard, "Suitable for most images."},
    {EUpscModelType_Lite, "Suitable for most images. High-speed upscaling with minimal quality loss."},
    {EUpscModelType_Fidelity, "For all Kinds of images with a focus on realistic details and smooth textures."},
    {EUpscModelType_Remacri, "For natural images. Added sharpness and detail. No commercial use."},
    {EUpscModelType_Ultramix, "For natural images with a balance of sharpness and detail."},
    {EUpscModelType_Ultrasharp, "For natural images with a focus on sharpness."},
    {EUpscModelType_Digital, "For digital art and illustrations."},
};

struct SUpscSelectModelData {
    EUpscModelType type;
    QString name;
    QString title;
    QString desc;
    QPixmap beforeThumb;
    QPixmap afterThumb;
};
Q_DECLARE_METATYPE(SUpscSelectModelData)

// crop
struct SUpscModelData {
    QString id = "";
    QString name = "";
    QString path = "";
    QPixmap thumbnail = QPixmap();
};
Q_DECLARE_METATYPE(SUpscModelData)