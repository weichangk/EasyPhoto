#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include <QPainter>
#include <QEvent>
#include <QPixmap>

class AGUI_EXPORT AFourStateImageWidget : public ABaseWidget
{
    Q_OBJECT
public:
    AFourStateImageWidget(QWidget *parent = 0);
    ~AFourStateImageWidget();
    void setFourPixmap(QPixmap pixmap);
    void setNormalPixmap(QPixmap pixmap);
    void setHoverPixmap(QPixmap pixmap);
    void setPressedPixmap(QPixmap pixmap);
    void setDisablePixmap(QPixmap pixmap);

protected:
    void paintEvent(QPaintEvent *event) override;
    void changeEvent(QEvent *event) override;

private:
    int m_State = 0; // 0 1 2 3 normal hover pressed disenabled
    QPixmap m_FourPixmap;
    QPixmap m_NormalPixmap;
    QPixmap m_HoverPixmap;
    QPixmap m_PressedPixmap;
    QPixmap m_DisabledPixmap;
};

