/*
 * @Author: weick 
 * @Date: 2024-06-03 07:33:48 
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:35:31
 */

#pragma once
#include "../agui/inc/abasewidget.h"
#include "inc/models.h"

namespace imageerase {
class ImageErasePreviewView : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageErasePreviewView(QWidget *parent = nullptr);
    ~ImageErasePreviewView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:

private:

};
} // namespace imageedit