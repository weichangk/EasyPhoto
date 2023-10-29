#include "inc/acanmovewidget.h"
#include <QMouseEvent>

ACanMoveWidget::ACanMoveWidget(QWidget *parent)
    : ABaseWidget(parent), m_parentWidget(parent)
{
}

ACanMoveWidget::~ACanMoveWidget()
{
}

void ACanMoveWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (contentsRect().contains(event->pos().rx(), event->pos().ry()))
        {
            if (m_parentWidget)
            {
                m_lastMousePos = event->globalPos() - m_parentWidget->geometry().topLeft();
                m_isMousePressed = true;
                m_pressRect = m_parentWidget->rect();
            }
        }
    }
    ABaseWidget::mousePressEvent(event);
}

void ACanMoveWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons().testFlag(Qt::LeftButton))
        return;
    if (m_isMousePressed == true && m_canMoveEnabled)
    {
        if (m_parentWidget)
        {
            auto pos = event->globalPos() - m_lastMousePos;
            m_parentWidget->setGeometry(QRect(pos.x(), pos.y(), m_pressRect.width(), m_pressRect.height()));
        }
    }
    ABaseWidget::mouseMoveEvent(event);
}

void ACanMoveWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isMousePressed = false;
    ABaseWidget::mouseReleaseEvent(event);
}
