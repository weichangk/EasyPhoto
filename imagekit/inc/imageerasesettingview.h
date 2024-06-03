/*
 * @Author: weick 
 * @Date: 2024-06-03 07:39:05 
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:43:08
 */

#pragma once
#include "../agui/inc/abasewidget.h"

namespace imageerase {
class ImageEraseSettingView : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageEraseSettingView(QWidget *parent = nullptr);
    ~ImageEraseSettingView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
};
} // namespace imageerase