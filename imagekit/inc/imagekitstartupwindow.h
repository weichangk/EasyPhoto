#pragma once
#include "imagekit_global.h"

class ATopbar;
class ACanMoveWidget;
class APushButton;
class ImageFuncView;
class IMAGEKIT_EXPORT ImageKitStartupWindow : public ABaseWidget
{
    Q_OBJECT
public:
    ImageKitStartupWindow(QWidget *parent = nullptr);
    ~ImageKitStartupWindow();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

    void paintEvent(QPaintEvent *event) override;

private:
    ATopbar * m_Topbar = nullptr;
    ACanMoveWidget * m_Navbar = nullptr;
    AWidget *m_FuncArea = nullptr;

    APushButton *m_LogoBtn = nullptr;
    APushButton *m_VipBtn = nullptr;
    APushButton *m_VipRightsBtn = nullptr;

    APushButton *m_FuncBtn = nullptr;
    APushButton *m_FilesBtn = nullptr;
    APushButton *m_SettingsBtn = nullptr;

    ImageFuncView *m_ImageFuncView = nullptr;
};
