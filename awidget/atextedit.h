#pragma once
#include "qtextedit.h"

class ATextEdit : public QTextEdit
{
    Q_OBJECT
public:
    ATextEdit(QWidget *parent = nullptr);
    ~ATextEdit();
    void setUseCustomTextCursor(bool b);
    void setCustomTextCursorColor(QColor color);

protected:
    void timerEvent(QTimerEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    bool m_useCustomTextCursor = false;
    QColor m_customTextCursorOriginalColor = Qt::transparent;
    QColor m_customTextCursorFlickerColor = Qt::black;
    int m_customTextCursorTimerId;
};
