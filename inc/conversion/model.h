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