/*
 * @Author: weick
 * @Date: 2023-12-05 23:01:22
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:01:22
 */

#pragma once
#include <QString>
#include <QPixmap>

class ImageFunc {
public:
    ImageFunc();
    ImageFunc(const QString &name, const QString &desc, const QPixmap &icon);

private:
    QString m_Name;
    QString m_Desc;
    QPixmap m_Icon;
};
