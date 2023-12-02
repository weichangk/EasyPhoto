#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include "astylestatus.h"
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
    void setState(StyleStatus state);

protected:
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void changeEvent(QEvent *event) override;

private:
    StyleStatus m_State = StyleStatus::Normal;
    QPixmap m_FourPixmap;
    QPixmap m_NormalPixmap;
    QPixmap m_HoverPixmap;
    QPixmap m_PressedPixmap;
    QPixmap m_DisabledPixmap;
};

