#pragma once

class QString;
class QWidget;
class StyleMgr
{
public:
    static void setStyleToApp(const QString &qssfolder);
    static void setStyleToWidget(QWidget *widget, const QString& fileName);
};
