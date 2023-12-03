#include "inc/anavbarwidget.h"
#include "../awidget/inc/avboxlayout.h"

ANavbarWidget::ANavbarWidget(QMap<int, QVariantList> data, QWidget *parent)
    : ABaseWidget(parent),
      m_Data(data)
{
    createUi();
    sigConnect();
}

ANavbarWidget::~ANavbarWidget()
{
}

void ANavbarWidget::createUi()
{
    auto mainLayout = new AVBoxLayout(this);
    QMap<int, QVariantList>::Iterator iter;
    for (iter = m_Data.begin(); iter != m_Data.end(); ++iter)
    {
        QPixmap pix(24 * 4, 24);
        pix.load(iter.value().at(0).toString());
        auto btn = new AIconTextWidget(this);
        btn->setObjectName("m_FuncBtn");
        btn->setFixedHeight(32);
        btn->getIcon()->setFixedSize(24, 24);
        btn->getIcon()->setFourPixmap(pix);
        btn->getText()->setText(iter.value().at(1).toString());
        connect(btn, &AIconTextWidget::sigClicked, this, [=]()
        {
            exclusive(btn);
            emit sigClicked(iter.key());
        });
        mainLayout->addWidget(btn);
    }
    mainLayout->addStretch();
}

void ANavbarWidget::changeLanguage()
{
}

void ANavbarWidget::sigConnect()
{
}

void ANavbarWidget::exclusive(AIconTextWidget *widget)
{
    if(!m_Exclusive)
    {
        QList<AIconTextWidget *> btns = findChildren<AIconTextWidget *>();
        for (int i = 0; i < btns.size(); i++)
        {
            btns[i]->setState(AEnum::StyleStatus::Normal);
        }
    }
    widget->setState(AEnum::StyleStatus::Checked);
}
