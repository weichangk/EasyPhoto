/*
 * @Author: weick 
 * @Date: 2024-06-03 07:39:05 
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:43:08
 */

#pragma once
#include "../agui/inc/abasewidget.h"

namespace image2gif {
class Image2GifSettingView : public ABaseWidget {
    Q_OBJECT
public:
    explicit Image2GifSettingView(QWidget *parent = nullptr);
    ~Image2GifSettingView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
};
} // namespace image2gif