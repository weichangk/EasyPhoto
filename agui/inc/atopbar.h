#pragma once
#include "agui_global.h"
#include "acanmovewidget.h"

class APushButton;
class AGUI_EXPORT ATopbar : public ACanMoveWidget
{
    Q_OBJECT
public:
    ATopbar(QWidget *parent);
    ~ATopbar();
    void setNormalVisible(bool visible);
    void setCloseBtnTopRight10Radius();

Q_SIGNALS:
    void sigMin();
    void sigMax();
    void sigNormal();
    void sigClose();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    APushButton *m_minBtn;
    APushButton *m_maxBtn;
    APushButton *m_normalBtn;
    APushButton *m_closeBtn;
    APushButton *m_minMacBtn;
    APushButton *m_maxMacBtn;
    APushButton *m_normalMacBtn;
    APushButton *m_closeMacBtn;
    QWidget *m_contentWidget;
};
