/*
 * @Author: weick 
 * @Date: 2024-03-23 11:06:40 
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 11:09:50
 */

#pragma once
#include "../agui/inc/abasewidget.h"

class EditFileListView : public ABaseWidget {
    Q_OBJECT
public:
    explicit EditFileListView(QWidget *parent = nullptr);
    ~EditFileListView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
};