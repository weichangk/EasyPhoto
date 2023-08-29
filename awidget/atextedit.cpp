#include "atextedit.h"
#include "qpainter.h"
#include "qcoreevent.h"

ATextEdit::ATextEdit(QWidget *parent) : QTextEdit(parent)
{
    setAttribute(Qt::WA_StyledBackground);
}

ATextEdit::~ATextEdit()
{
}

void ATextEdit::timerEvent(QTimerEvent *e)
{
    if (m_useCustomTextCursor && e->timerId() == m_customTextCursorTimerId)
    {
        if (m_customTextCursorOriginalColor != m_customTextCursorFlickerColor)
        {
            m_customTextCursorOriginalColor = m_customTextCursorFlickerColor;
        }
        else
        {
            m_customTextCursorOriginalColor = Qt::transparent;
        }
        update();
    }
    else
    {
        QTextEdit::timerEvent(e);
    }
}

void ATextEdit::paintEvent(QPaintEvent *e)
{
    QTextEdit::paintEvent(e);

    if(m_useCustomTextCursor)
    {
        setCursorWidth(0);
        QPainter painter(viewport());
        painter.setPen(m_customTextCursorOriginalColor);
        painter.drawRect(cursorRect());
    }
}

void ATextEdit::focusInEvent(QFocusEvent *event)
{
    QTextEdit::focusInEvent(event);

    if(m_useCustomTextCursor)
    {
        m_customTextCursorOriginalColor = m_customTextCursorFlickerColor;
        update();
        m_customTextCursorTimerId = startTimer(500);
    }
}

void ATextEdit::focusOutEvent(QFocusEvent *e)
{
    QTextEdit::focusOutEvent(e);

    if(m_useCustomTextCursor)
    {
        killTimer(m_customTextCursorTimerId);
        m_customTextCursorOriginalColor = Qt::transparent;
        update();
    }
}

void ATextEdit::setUseCustomTextCursor(bool b)
{
    m_useCustomTextCursor = b;
}

void ATextEdit::setCustomTextCursorColor(QColor color)
{
    m_customTextCursorFlickerColor = color;
}
