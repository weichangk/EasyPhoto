#include "inc/abasewidget.h"
#include <QEvent>

ABaseWidget::ABaseWidget(QWidget *parent) : AWidget(parent)
{

}

ABaseWidget::~ABaseWidget()
{
}

bool ABaseWidget::event(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        changeLanguage();
    }
    return AWidget::event(e);
}
