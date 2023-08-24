#pragma once
#include <QApplication>
#include <QWidget>
#include <QtCore/qdir.h>

class StyleMgr
{
public:
    static void setStyleToAppByCssFolder(const QString &qssfolder);
    static void setStyleToWidgetByCssFile(QWidget *widget, const QString& fileName);
};
