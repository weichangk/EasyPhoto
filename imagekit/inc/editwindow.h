/*
 * @Author: weick
 * @Date: 2024-03-23 10:56:22
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 11:02:24
 */

#pragma once
#include "../agui/inc/abasewidget.h"

class EditWindow : public ABaseWidget {
    Q_OBJECT
public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
};