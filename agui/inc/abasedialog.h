/*
 * @Author: weick
 * @Date: 2024-07-06 14:34:58
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-06 14:45:41
 */

#pragma once
#include "agui_global.h"
#include "../awidget/inc/adialog.h"

class AGUI_EXPORT ABaseDialog : public ADialog {
    Q_OBJECT
public:
    ABaseDialog(QDialog *parent = nullptr);
    ~ABaseDialog();

protected:
    bool event(QEvent *e) override;

    virtual void createUi(){};
    virtual void changeLanguage(){};
    virtual void sigConnect(){};
};