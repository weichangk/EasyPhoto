#pragma once
#include "funcenum.h"

#include <QString>
#include <QPixmap>

using EFuncItemBtnType = enum {
    StartNow = 0,
    AddFile,
};

struct SFuncItemData {
    EFunc func;
    EFuncItemBtnType btn_type;
    QString title = "";
    QString desc = "";
    bool is_new = false;
    bool is_ai = false;
    QPixmap thumbnail = QPixmap();
    QPixmap new_icon = QPixmap();
    QPixmap ai_icon = QPixmap();
    QPixmap startnew_icon = QPixmap();
    QPixmap addfile_icon = QPixmap();
};
Q_DECLARE_METATYPE(SFuncItemData)