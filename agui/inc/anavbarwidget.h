#pragma once
#include "agui_global.h"
#include "abasewidget.h"

class AGUI_EXPORT ANavbarWidget : public ABaseWidget
{
    Q_OBJECT
public:
    ANavbarWidget(QWidget *parent = nullptr);
    ~ANavbarWidget();
};

class AGUI_EXPORT ANavbarItemWidget : public ABaseWidget
{
    Q_OBJECT
public:
    ANavbarItemWidget(QWidget *parent = nullptr);
    ~ANavbarItemWidget();
};
