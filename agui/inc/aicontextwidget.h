#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include "afourstateimagewidget.h"
#include "../awidget/inc/alabel.h"

class AGUI_EXPORT AIconTextWidget : public ABaseWidget
{
public:
    AIconTextWidget(QWidget *parent = nullptr);
    ~AIconTextWidget();

protected:
    void createUi() override;

private:
    AFourStateImageWidget *m_Icon = nullptr;
    ALabel *m_Text = nullptr;
};
