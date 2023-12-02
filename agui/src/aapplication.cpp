#include "inc/aapplication.h"
#include "inc/atooltip.h"
#include <QEvent>
#include <QHelpEvent>

AApplication::AApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{

}

bool AApplication::event(QEvent *event)
{
    // if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    // {
    //     QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    //     if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
    //     {
    //         // 阻止系统级Enter键事件
    //         return true;
    //     }
    // }
    return QApplication::event(event);
}
bool AApplication::notify(QObject *object, QEvent *event)
{
	if (event->type() == QEvent::ToolTip)
	{
		if (QWidget *widget = qobject_cast<QWidget*>(object))
		{
			if (!widget->toolTip().isEmpty())
			{
                if(!AToolTip::getInstance()->isVisible())
                {
                    AToolTip::getInstance()->showText(widget->toolTip(), static_cast<QHelpEvent*>(event)->globalPos());
                }
                return true;
			}
		}
	}
    else if (event->type() == QEvent::Leave)
    {
        AToolTip::getInstance()->hideText();
    }
    return QApplication::notify(object, event);
}
