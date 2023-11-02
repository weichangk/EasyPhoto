#include "inc/imagefunc.h"

ImageFunc::ImageFunc()
{
}

ImageFunc::ImageFunc(const QString& name, const QString& desc, const QPixmap& icon)
{
    m_Name = name;
    m_Desc = desc;
    m_Icon = icon;
}
