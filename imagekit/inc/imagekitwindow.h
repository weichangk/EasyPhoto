#pragma once
#include "../agui/inc/abasewidget.h"

class ImageKitWindow : public ABaseWidget
{
    Q_OBJECT
public:
    ImageKitWindow(QWidget *parent = nullptr);
    ~ImageKitWindow();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
};
