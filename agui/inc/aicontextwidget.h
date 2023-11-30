#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include "afourstateimagewidget.h"
#include "../awidget/inc/alabel.h"

class AGUI_EXPORT AIconTextWidget : public ABaseWidget
{
    Q_OBJECT
public:
    AIconTextWidget(QWidget *parent = nullptr);
    ~AIconTextWidget();
    AFourStateImageWidget *getIcon() { return m_Icon; }
    ALabel *getText() { return m_Text; }
    void setIconLeftSpacing(int spacing) { m_IconLeftSpacing = spacing; }
    void setIconRightSpacing(int spacing) { m_IconRightSpacing = spacing; }

Q_SIGNALS:
    void sigClicked();

protected:
    void createUi() override;

private:
    AFourStateImageWidget *m_Icon = nullptr;
    ALabel *m_Text = nullptr;
    int m_IconLeftSpacing = 8;
    int m_IconRightSpacing = 8;
};
