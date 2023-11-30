#include "inc/afourstateimagewidget.h"

AFourStateImageWidget::AFourStateImageWidget(QWidget *parent) : ABaseWidget(parent)
{
}

AFourStateImageWidget::~AFourStateImageWidget()
{
}

void AFourStateImageWidget::setFourPixmap(QPixmap pixmap)
{
    m_FourPixmap = pixmap;
    m_NormalPixmap = m_FourPixmap.copy(0, 0, m_FourPixmap.width() / 4, m_FourPixmap.height());
    m_HoverPixmap = m_FourPixmap.copy(m_FourPixmap.width() / 4, 0, m_FourPixmap.width() / 4, m_FourPixmap.height());
    m_PressedPixmap = m_FourPixmap.copy(m_FourPixmap.width() / 2, 0, m_FourPixmap.width() / 4, m_FourPixmap.height());
    m_DisabledPixmap = m_FourPixmap.copy(m_FourPixmap.width() / 4 * 3, 0, m_FourPixmap.width() / 4, m_FourPixmap.height());
}

void AFourStateImageWidget::setNormalPixmap(QPixmap pixmap)
{
    m_NormalPixmap = pixmap;
}

void AFourStateImageWidget::setHoverPixmap(QPixmap pixmap)
{
    m_HoverPixmap = pixmap;
}

void AFourStateImageWidget::setPressedPixmap(QPixmap pixmap)
{
    m_PressedPixmap = pixmap;
}

void AFourStateImageWidget::setDisablePixmap(QPixmap pixmap)
{
    m_DisabledPixmap = pixmap;
}

void AFourStateImageWidget::showEvent(QShowEvent *event)
{
    ABaseWidget::showEvent(event);
}

void AFourStateImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    if (!m_FourPixmap.isNull())
    {
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
    }
    else
    {
        switch (m_State)
        {
        case 1:
            m_HoverPixmap.setDevicePixelRatio(1);
            painter.drawPixmap(this->rect(), m_HoverPixmap);
            break;
        case 2:
            m_PressedPixmap.setDevicePixelRatio(1);
            painter.drawPixmap(this->rect(), m_PressedPixmap);
            break;
        case 3:
            m_DisabledPixmap.setDevicePixelRatio(1);
            painter.drawPixmap(this->rect(), m_DisabledPixmap);
            break;
        default:
            m_NormalPixmap.setDevicePixelRatio(1);
            painter.drawPixmap(this->rect(), m_NormalPixmap);
            break;
        }
    }
    ABaseWidget::paintEvent(event);
}

void AFourStateImageWidget::mousePressEvent(QMouseEvent *event)
{
    ABaseWidget::mousePressEvent(event);
    m_State = 2;
    update();
}

void AFourStateImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    ABaseWidget::mouseReleaseEvent(event);
    m_State = 0;
    update();
}

void AFourStateImageWidget::enterEvent(QEnterEvent *event)
{
    ABaseWidget::enterEvent(event);
    m_State = 1;
    update();
}

void AFourStateImageWidget::leaveEvent(QEvent *event)
{
    ABaseWidget::leaveEvent(event);
    m_State = 0;
    update();
}

void AFourStateImageWidget::changeEvent(QEvent *event)
{
    ABaseWidget::changeEvent(event);
    if (event->type() == QEvent::EnabledChange)
    {
        if (!isEnabled())
        {
            m_State = 3;
            update();
        }
    }
}
