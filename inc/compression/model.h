#pragma once

#include <QString>
#include <QPixmap>

#define COMP_OUT_FORMATS "sameassource jpg png"
#define COMP_OUT_QUALITY "10 20 30 40 50 60 70 80 90"

struct SCompressionData {
    QString file_name = "";
    QString file_path = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
    QPixmap checked_icon = QPixmap();
    QPixmap unchecked_icon = QPixmap();
    bool is_checked = false;
};
Q_DECLARE_METATYPE(SCompressionData)

struct SCompressionOuputFormat {
    QString name = "";
    QString des = "";
    QPixmap icon = QPixmap();
    bool checked = false;
};
Q_DECLARE_METATYPE(SCompressionOuputFormat)