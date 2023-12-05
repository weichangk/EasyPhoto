/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:08
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:03:08
 */

#include "inc/imagefunc.h"

ImageFunc::ImageFunc() {
}

ImageFunc::ImageFunc(const QString &name, const QString &desc, const QPixmap &icon) {
    m_Name = name;
    m_Desc = desc;
    m_Icon = icon;
}
