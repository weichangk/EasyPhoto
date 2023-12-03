#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include <QPixmap>

class AGUI_EXPORT AThumbnail : public ABaseWidget
{
    Q_OBJECT
public:
    AThumbnail(QWidget *parent = nullptr);
    ~AThumbnail();

    void setPixmap(QPixmap pixmap) { m_pixmap = pixmap; update(); };
    void setRadiius(int radiius) { m_radiius = radiius; update(); };
    void setHasBorder(bool b) { m_hasBorder = b; };

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QPixmap m_pixmap = QPixmap();
    int m_radiius = 6;
    bool m_hasBorder = false;
};
