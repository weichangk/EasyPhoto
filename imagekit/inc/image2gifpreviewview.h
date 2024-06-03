/*
 * @Author: weick 
 * @Date: 2024-06-03 07:33:48 
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:35:31
 */

#pragma once
#include "../agui/inc/abasewidget.h"
#include "inc/models.h"

namespace image2gif {
class Image2GifPreviewView : public ABaseWidget {
    Q_OBJECT
public:
    explicit Image2GifPreviewView(QWidget *parent = nullptr);
    ~Image2GifPreviewView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:

private:

};
} // namespace imageedit