#include "awidget.h"
#include "acore/langmgr.h"

AWidget::AWidget(QWidget *parent) : QWidget(parent)
{
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
