#pragma once

class QString;
class QWidget;
class StyleMgr
{
public:
    static void setStyleToApp(const QString &qssFolder);
    static void setStyleToWidget(QWidget *widget, const QString& fileName);
};
