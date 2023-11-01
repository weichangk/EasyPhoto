#pragma once
#include "imagekit_global.h"

class ATopbar;
class ACanMoveWidget;
class IMAGEKIT_EXPORT ImageKitStartupView : public ABaseWidget
{
    Q_OBJECT
public:
    ImageKitStartupView(QWidget *parent = nullptr);
    ~ImageKitStartupView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

    void paintEvent(QPaintEvent *event) override;

private:
    ATopbar * m_Topbar = nullptr;
    ACanMoveWidget * m_Navbar = nullptr;
    AWidget *m_FuncArea = nullptr;
};
