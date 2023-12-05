/*
 * @Author: weick
 * @Date: 2023-12-05 22:52:58
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:52:58
 */

#pragma once
#include "agui_global.h"
#include "abasewidget.h"

class QFrame;
class QLabel;
class AGUI_EXPORT AToolTip : public ABaseWidget {
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
