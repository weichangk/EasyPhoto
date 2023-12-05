/*
 * @Author: weick
 * @Date: 2023-12-05 22:51:12
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:51:12
 */

#pragma once
#include "agui_global.h"

class AGUI_EXPORT ABaseWidget : public AWidget {
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
