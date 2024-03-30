/*
 * @Author: weick
 * @Date: 2024-03-23 11:23:05
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-30 08:56:45
 */

#pragma once
#include "../agui/inc/abasewidget.h"
#include "../awidget/inc/atabbar.h"
#include "../awidget/inc/atabwidget.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/apushbutton.h"   

namespace imageedit {
class EditSettingView : public ABaseWidget {
    Q_OBJECT
public:
    explicit EditSettingView(QWidget *parent = nullptr);
    ~EditSettingView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    ATabBar *tab_bar_;
    ATabWidget *tab_widget_;
    AWidget *crop_setting_widget_;
    AWidget *effect_setting_widget_;
    AWidget *watermark_setting_widget_;
    APushButton *export_button_;
};
} // namespace imageedit