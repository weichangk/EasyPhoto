/*
 * @Author: weick
 * @Date: 2023-12-10 22:25:46
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-14 00:02:40
 */

#pragma once
#include "../agui/inc/arotatingpixmapwidget.h"
#include <QObject>
#include <QString>
#include <QPixmap>

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
    bool m_IsAdd = false;
    QString m_FileName = "";
    QString m_FilePath = "";
    ConversionModels::ConversionType m_ConversionType = ConversionModels::ConversionType::None;
    QPixmap m_Thumbnail = QPixmap();
    QPixmap m_DelIcon = QPixmap();
};
Q_DECLARE_METATYPE(ConversionData)
