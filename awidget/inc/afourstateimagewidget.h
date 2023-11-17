#pragma once
#include "awidget_global.h"
#include "awidget.h"
#include <QPainter>
#include <QEvent>
#include <QPixmap>

class AWIDGET_EXPORT AFourStateImageWidget : public AWidget
{
    Q_OBJECT
public:
    AFourStateImageWidget(QWidget *parent = 0);
    ~AFourStateImageWidget();
    void setPixmap(QPixmap pixmap);

protected:
    void paintEvent(QPaintEvent *event) override;
    void changeEvent(QEvent *event) override;

private:
    int m_State = 0; // 0 1 2 3 normal hover pressed disenabled
    QPixmap m_Pixmap;
    QPixmap m_NormalPixmap;
    QPixmap m_HoverPixmap;
    QPixmap m_PressedPixmap;
    QPixmap m_DisabledPixmap;
};

AFourStateImageWidget::AFourStateImageWidget(QWidget *parent) : AWidget(parent)
{
}

AFourStateImageWidget::~AFourStateImageWidget()
{
}

void AFourStateImageWidget::setPixmap(QPixmap pixmap)
{
    m_Pixmap = pixmap;
    m_NormalPixmap = m_Pixmap.copy(0, 0, m_Pixmap.width() / 4, m_Pixmap.height());
    m_HoverPixmap = m_Pixmap.copy(m_Pixmap.width() / 4, 0, m_Pixmap.width() / 4, m_Pixmap.height());
    m_PressedPixmap = m_Pixmap.copy(m_Pixmap.width() / 2, 0, m_Pixmap.width() / 4, m_Pixmap.height());
    m_DisabledPixmap = m_Pixmap.copy(m_Pixmap.width() / 4 * 3, 0, m_Pixmap.width() / 4, m_Pixmap.height());
}

void AFourStateImageWidget::paintEvent(QPaintEvent *event)
{
    if (m_Pixmap.isNull())
    {
        return;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPixmap pixmapTemp;
    switch (m_State)
    {
    case 1:
        pixmapTemp = m_HoverPixmap.scaled(this->rect().size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixmapTemp.setDevicePixelRatio(1);
        painter.drawPixmap(this->rect(), pixmapTemp);
        break;
    case 2:
        pixmapTemp = m_PressedPixmap.scaled(this->rect().size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixmapTemp.setDevicePixelRatio(1);
        painter.drawPixmap(this->rect(), pixmapTemp);
        break;
    case 3:
        pixmapTemp = m_DisabledPixmap.scaled(this->rect().size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixmapTemp.setDevicePixelRatio(1);
        painter.drawPixmap(this->rect(), pixmapTemp);
        break;
    default:
        pixmapTemp = m_NormalPixmap.scaled(this->rect().size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixmapTemp.setDevicePixelRatio(1);
        painter.drawPixmap(this->rect(), pixmapTemp);
        break;
    }
    AWidget::paintEvent(event);
}

void AFourStateImageWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::Enter)
    {
        m_State = 1;
        update();
    }
    if (event->type() == QEvent::Leave)
    {
        m_State = 0;
        update();
    }
    if (event->type() == QEvent::MouseButtonPress)
    {
        m_State = 2;
        update();
    }
    if (event->type() == QEvent::MouseButtonRelease)
    {
        m_State = 0;
        update();
    }
    if (event->type() == QEvent::EnabledChange)
    {
        if (!isEnabled())
        {
            m_State = 3;
            update();
        }
    }
    AWidget::changeEvent(event);
}
