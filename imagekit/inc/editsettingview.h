/*
 * @Author: weick
 * @Date: 2024-03-23 11:23:05
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 11:23:52
 */

#pragma once
#include "../agui/inc/abasewidget.h"

class EditSettingView : public ABaseWidget {
    Q_OBJECT
public:
    explicit EditSettingView(QWidget *parent = nullptr);
    ~EditSettingView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
};