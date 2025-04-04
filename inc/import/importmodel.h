#pragma once

#include <QString>
#include <QPixmap>

struct SImportListItem {
    QString name = "";
    QString path = "";
    QPixmap thumbnail = QPixmap();
    QPixmap delete_icon = QPixmap();
};
Q_DECLARE_METATYPE(SImportListItem)