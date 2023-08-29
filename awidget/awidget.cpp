#include "awidget.h"
#include "acore/langmgr.h"

AWidget::AWidget(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
    setAttribute(Qt::WA_StyledBackground);
}

AWidget::~AWidget()
{
}

void AWidget::changeLanguage()
{
}

void AWidget::sigConnect()
{
    connect(LangMgr::getInstance(), &LangMgr::sigChangeLanguage, this, &AWidget::changeLanguage);
}
