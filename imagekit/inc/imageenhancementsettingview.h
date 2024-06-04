/*
 * @Author: weick 
 * @Date: 2024-06-04 08:00:37 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:00:37 
 */

#pragma once
#include "../agui/inc/abasewidget.h"

namespace imageenhancement {
class ImageEnhancementSettingView : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageEnhancementSettingView(QWidget *parent = nullptr);
    ~ImageEnhancementSettingView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
};
} // namespace imageenhancement