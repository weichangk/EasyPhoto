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
    QString output_format = Default::conversionOutFormat;
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

#define COMP_INPUT_FORMATS "(*.jpg *.jpeg *.png *.gif *.webp)"
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
    QString output_format = Default::compressionOutFormat;
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


#define ENHANCE_INPUT_FORMATS "png jpg jpeg webp"
#define ENHANCE_OUTPUT_FORMATS "png jpg webp"

struct SUpscModelData {
    QString id = "";
    QString name = "";
    QString path = "";
    QPixmap thumbnail = QPixmap();
};
Q_DECLARE_METATYPE(SUpscModelData)