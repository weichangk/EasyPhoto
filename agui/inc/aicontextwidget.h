#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include "aenum.h"
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
    void setState(AEnum::StyleStatus state);
    void setIconTextSpacing(int spacing) { m_IconTextSpacing = spacing; }

Q_SIGNALS:
    void sigClicked();

protected:
    void createUi() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void changeEvent(QEvent *event) override;

private:
    AEnum::StyleStatus m_State = AEnum::StyleStatus::Normal;
    AFourStateImageWidget *m_Icon = nullptr;
    ALabel *m_Text = nullptr;
    int m_IconTextSpacing = 6;
};
