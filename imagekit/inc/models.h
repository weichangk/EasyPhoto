/*
 * @Author: weick
 * @Date: 2023-12-09 23:52:37
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-10 14:51:10
 */

#pragma once
#include <QObject>
#include <QPixmap>

#define COMPRESS_OUT_FORMATS "sameassource jpg png"
#define COMPRESS_OUT_QUALITY "10 20 30 40 50 60 70 80 90"

class Models : public QObject {
    Q_OBJECT
public:
    enum Funcs {
        Startup = 0,
        ImageConversion,    // 图片转换
        ImageCompression,   // 图片压缩
        ImageCropping,      // 图片裁剪
        ImageAmplification, // 图像放大
        ImageManipulation,  // 图片抠像
        ImageErase,         // 图片擦除
        ImageEnhancement,   // 图像增强
        ImageRestoration,   // 图像复原
        ImageEffect,        // 图片效果
        ImageSpecialEffect  // 图片特效
    };
    Q_ENUM(Funcs)

    enum ConvStatusEnum {
        None = 0,
        Start,
        Finished,
        Cancel
    };
    Q_ENUM(ConvStatusEnum)

    enum CompressStatusEnum {
        Compress_None = 0,
        Compress_Start,
        Compress_Finished,
        Compress_Cancel
    };
    Q_ENUM(CompressStatusEnum)

    struct CompressionData {
        QString m_FileName = "";
        QString m_FilePath = "";
        CompressStatusEnum m_CompressState = CompressStatusEnum::Compress_None;
        QPixmap m_Thumbnail = QPixmap();
        QPixmap m_DelIcon = QPixmap();
        QPixmap m_CheckedIcon = QPixmap();
        QPixmap m_UnCheckedIcon = QPixmap();
        bool m_IsChecked = false;
    };
};
