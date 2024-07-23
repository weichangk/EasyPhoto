/*
 * @Author: weick 
 * @Date: 2024-06-04 08:00:37 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:00:37 
 */

#pragma once
#include "../agui/inc/abasewidget.h"

namespace imageupscayl {
class ImageUpscaylSettingView : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageUpscaylSettingView(QWidget *parent = nullptr);
    ~ImageUpscaylSettingView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
};
} // namespace imageupscayl