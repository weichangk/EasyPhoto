#pragma once
#include <QString>
#include <QPixmap>

class ImageFunc
{
public:
    ImageFunc();
    ImageFunc(const QString& name, const QString& desc, const QPixmap& icon);
private:
    QString m_Name;
    QString m_Desc;
    QPixmap m_Icon;
};
