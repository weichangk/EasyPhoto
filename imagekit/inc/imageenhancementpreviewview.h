/*
 * @Author: weick 
 * @Date: 2024-06-04 08:00:32 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:00:32 
 */

#pragma once
#include "../agui/inc/abasewidget.h"
#include "inc/models.h"

namespace imageenhancement {
class ImageEnhancementPreviewView : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageEnhancementPreviewView(QWidget *parent = nullptr);
    ~ImageEnhancementPreviewView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:

private:

};
} // namespace imageenhancement