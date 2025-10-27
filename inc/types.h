#pragma once

#include "settings.h"

#include <QString>
#include <QPixmap>

enum EImageState {
    EImageState_Waiting = 0,
    EImageState_Loading,
    EImageState_Success,
    EImageState_Fail,
};
struct SImageData {
    QString file_name = "";
    QString file_path = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    QMap<EImageState, QPixmap> state_icons;
    bool is_checked = false;
    QSize resolution = QSize(0, 0);
    QString output_format = Default::Conv::outFormat;
    QString intput_size = "";
    QString output_size = "";
    EImageState state = EImageState_Waiting;
};
Q_DECLARE_METATYPE(SImageData)

// CONV
// 暂不持支：svg ico cur xpm heic jfif heif jif rgf xwd jfi picon
#define CONV_INPUT_FORMATS "(*.jpg;*.jpeg;*.webp;*.hdr;*.bmp;*.gif;*.dds;*.psd;*.tiff;*.tga;*.rgb;*.avif;*.pgm;*.jp2;*.rgba;*.ppm;*.xbm;*.pcx;*.wbmp;*.exr;*.map;*.jbg;*.pnm;*.jpe;*.yuv;*.pbm;*.pdb;*.g4;*.ras;*.g3;*.pal;*.sgi;*.pict;*.pfm;*.pcd;*.jps;*.uyvy;*.pgx;*.vips;*.six;*.fts;*.fax;*.jbig;*.ipl;*.sun;*.pam;*.viff;*.mng;*.mtv;*.xv;*.pct;*.sixel;*.palm;*.rgbo;*.hrz;*.otb;*.JPG;*.JPEG;*.WEBP;*.HDR;*.BMP;*.GIF;*.DDS;*.PSD;*.TIFF;*.TGA;*.RGB;*.AVIF;*.PGM;*.JP2;*.RGBA;*.PPM;*.XBM;*.PCX;*.WBMP;*.EXR;*.MAP;*.JBG;*.PNM;*.JPE;*.YUV;*.PBM;*.PDB;*.G4;*.RAS;*.G3;*.PAL;*.SGI;*.PICT;*.PFM;*.PCD;*.JPS;*.UYVY;*.PGX;*.VIPS;*.SIX;*.FTS;*.FAX;*.JBIG;*.IPL;*.SUN;*.PAM;*.VIFF;*.MNG;*.MTV;*.XV;*.PCT;*.SIXEL;*.PALM;*.RGBO;*.HRZ;*.OTB)"
const QMap<QString, QString> CONV_OUTPUT_FORMATS{
    {"jpg", "JPG"},
    {"png", "PNG"},
    {"webp", "WEBP"},
    {"svg", "SVG"},
    {"avif", "AVIF"},
    {"bmp", "BMP"},
    {"ico", "ICO"},
    {"tiff", "TIFF"},
    {"psd", "PSD"},
    {"eps", "EPS"},
    {"xbm", "XBM"},
};

// COMP
#define COMP_INPUT_FORMATS "(*.jpg;*.jpeg;*.png;*.gif;*.webp;*.JPG;*.JPEG;*.PNG;*.GIF;*.WEBP)"
const QMap<QString, QString> COMP_OUT_FORMATS{
    {"sameassource", "SAMEASSOURCE"},
    {"jpg", "JPG"},
    {"png", "PNG"},
};
const QMap<QString, QString> COMP_OUT_QUALITYS{
    {"10", "10%"},
    {"20", "20%"},
    {"30", "30%"},
    {"40", "40%"},
    {"50", "50%"},
    {"60", "60%"},
    {"70", "70%"},
    {"80", "80%"},
    {"90", "90%"},
};

// BGRM
#define BGRM_INPUT_FORMATS "(*.png;*.jpg;*.jpeg;*.bmp)"
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

// CROP
#define CROP_INPUT_FORMATS "(*.jpg;*.jpeg;*.webp)"
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
struct SUpscModelData {
    QString id = "";
    QString name = "";
    QString path = "";
    QPixmap thumbnail = QPixmap();
};
Q_DECLARE_METATYPE(SUpscModelData)

// ERASE
#define ERASE_INPUT_FORMATS "(*.png;*.jpg;*.jpeg;*.webp;*.bmp)"

// GIFMK
#define GIFMK_INPUT_FORMATS "(*.jpg;*.jpeg;*.png;*.bmp)"
#define GIFMK_OUTPUT_MINFRAMERATE 1
#define GIFMK_OUTPUT_MAXFRAMERATE 60
const QMap<QString, QString> GIFMK_SIZES {
    {"Custom", "2276 × 1280"},
    {"Original", "2276 × 1280"},
    {"240p", "426 × 240"},
    {"360p", "640 × 360"},
    {"450p", "800 × 450"},
    {"480p", "854 × 480"},
    {"750p", "1334 × 750"},
};
const QMap<QString, QString> GIFMK_SCALES {
    {"Custom", "Custom"},
    {"Original", "Original"},
    {"1:1", "1:1"},
    {"16:9", "16:9"},
    {"9:16", "9:16"},
    {"4:3", "4:3"},
    {"3:4", "3:4"},
    {"3:2", "3:2"},
    {"2:3", "2:3"},
};

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
