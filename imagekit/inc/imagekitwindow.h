#pragma once
#include "imagekit_global.h"

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
