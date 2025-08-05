#pragma once

#include "settings.h"

#include <QString>
#include <QPixmap>

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