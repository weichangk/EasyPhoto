/*
 * @Author: weick 
 * @Date: 2024-04-12 07:40:35 
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-12 07:48:42
 */

#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include "../awidget/inc/apushbutton.h"

class AGUI_EXPORT AImportGuide : public ABaseWidget {
    Q_OBJECT
public:
    explicit AImportGuide(QWidget *parent = nullptr);
    ~AImportGuide();

Q_SIGNALS:
    void sigClicked();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    
private:
    APushButton *import_btn_;
};