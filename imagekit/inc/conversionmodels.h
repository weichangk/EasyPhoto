/*
 * @Author: weick
 * @Date: 2023-12-10 22:25:46
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-15 23:14:30
 */

#pragma once
#include "../agui/inc/arotatingpixmapwidget.h"
#include <QObject>
#include <QString>
#include <QPixmap>

// 暂不持支：svg ico cur xpm heic jfif heif jif rgf xwd jfi picon
#define CONV_OUT_FORMATS "jpg jpeg webp hdr bmp gif dds psd tiff tga rgb avif pgm jp2 rgba ppm xbm pcx wbmp exr map jbg pnm jpe yuv pbm pdb g4 ras g3 pal sgi pict pfm pcd jps uyvy pgx vips six fts fax jbig ipl sun pam viff mng mtv xv pct sixel palm rgbo hrz otb"

class ConversionModels : public QObject {
    Q_OBJECT
public:
    enum ConversionType {
        None = 0,
        InConvert,
        Success,
        Fail
    };
    Q_ENUM(ConversionType)
};

struct ConversionData {
    QString m_FileName = "";
    QString m_FilePath = "";
    ConversionModels::ConversionType m_ConversionType = ConversionModels::ConversionType::None;
    QPixmap m_Thumbnail = QPixmap();
    QPixmap m_DelIcon = QPixmap();
    QPixmap m_CheckedIcon = QPixmap();
    QPixmap m_UnCheckedIcon = QPixmap();
    bool m_IsChecked = false;
};
Q_DECLARE_METATYPE(ConversionData)
