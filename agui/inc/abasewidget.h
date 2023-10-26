#pragma once
#include "agui_global.h"

class AGUI_EXPORT ABaseWidget : public AWidget
{
    Q_OBJECT
public:
    ABaseWidget(QWidget *parent = nullptr);
    ~ABaseWidget();

protected:
    bool event(QEvent *e) override;

    virtual void createUi(){};
    virtual void changeLanguage(){};
    virtual void sigConnect(){};
};
