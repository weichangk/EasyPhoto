#include "apushbutton.h"
#include "qpainter.h"
#include "qpainterpath.h"

APushButton::APushButton(QWidget *parent) : QPushButton(parent)
{
    setAttribute(Qt::WA_StyledBackground);
}

APushButton::~APushButton()
{
}

void APushButton::paintEvent(QPaintEvent *event)
{
    //  QPainter painter (this);
    //  painter.setRenderHint (QPainter :: Antialiasing); // Anti-aliasing;
    //  painter.setBrush (QBrush (Qt :: red));
    //  painter.setPen (Qt :: transparent);
    //  QRect rect = this-> rect ();
    //  rect.setWidth (rect.width ()-1);
    //  rect.setHeight (rect.height ()-1);
    //  painter.drawRoundedRect (rect, 15, 15);
    //  // You can also use QPainterPath to draw instead of painter.drawRoundedRect (rect, 15, 15);
    //  {
    //      QPainterPath painterPath;
    //      painterPath.addRoundedRect (rect, 15, 15);
    //      painter.drawPath (painterPath);
    //  }
    QPushButton::paintEvent(event);
}
