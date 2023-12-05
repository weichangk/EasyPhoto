/*
 * @Author: weick
 * @Date: 2023-12-05 23:01:53
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:01:53
 */

#pragma once
#include "../agui/inc/abasewidget.h"

class ImageKitWindow : public ABaseWidget {
    Q_OBJECT
public:
    ImageKitWindow(QWidget *parent = nullptr);
    ~ImageKitWindow();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
};
