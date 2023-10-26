#pragma once
#include "awidget_global.h"

class AWIDGET_EXPORT AShadowEffect: public QObject
{
    Q_OBJECT
public:
    AShadowEffect(QWidget *parent);
    ~AShadowEffect();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QPixmap ninePatchPixmap(const QPixmap& srcPixmap, int horzSplit, int vertSplit, int dstWidth, int dstHeight);

private:
    QWidget *m_parentWidget;
    QWidget *m_shadowWidget;
    QPixmap  m_pixmap;
    QPixmap  m_maskPixmap;
};
