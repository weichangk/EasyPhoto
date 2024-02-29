/*
 * @Author: weick
 * @Date: 2023-12-10 22:25:46
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-15 23:14:30
 */

#pragma once
#include <QObject>
#include <QString>
#include <QPixmap>

#define COMPRESS_OUT_FORMATS "jpg png"

class CompressionModels : public QObject {
    Q_OBJECT
public:
    enum CompressionType {
        None = 0,
        InCompress,
        Success,
        Fail
    };
    Q_ENUM(CompressionType)
};

struct CompressionData {
    QString m_FileName = "";
    QString m_FilePath = "";
    CompressionModels::CompressionType m_CompressionType = CompressionModels::CompressionType::None;
    QPixmap m_Thumbnail = QPixmap();
    QPixmap m_DelIcon = QPixmap();
    QPixmap m_CheckedIcon = QPixmap();
    QPixmap m_UnCheckedIcon = QPixmap();
    bool m_IsChecked = false;
};
Q_DECLARE_METATYPE(CompressionData)
