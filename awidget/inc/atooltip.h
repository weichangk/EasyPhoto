#pragma once
#include "awidget_global.h"
#include "awidget.h"

class QFrame;
class QLabel;
class AWIDGET_EXPORT AToolTip : public AWidget
{
    Q_OBJECT
public:
    static AToolTip *getInstance();
    static void release();
    void showText(const QString &text, QPoint pos = QCursor::pos());
    void hideText();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    AToolTip();

public:
    QFrame *m_frame = nullptr;
    QLabel *m_text = nullptr;
};
