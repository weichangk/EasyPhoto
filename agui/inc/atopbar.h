#pragma once
#include "agui_global.h"
#include "abasewidget.h"

class APushButton;
class AGUI_EXPORT ATopbar : public ABaseWidget
{
    Q_OBJECT
public:
    ATopbar(QWidget *parent);
    ~ATopbar();
    void canMoveEnabled(bool enabled) { m_canMoveEnabled = enabled; }
    void setNormalVisible(bool visible);

Q_SIGNALS:
    void sigMin();
    void sigMax();
    void sigNormal();
    void sigClose();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QWidget *m_parentWidget;
    bool m_canMoveEnabled = true;
    bool m_isMousePressed;
    QPoint m_lastMousePos;
    QRect m_pressRect;
    APushButton *m_minBtn;
    APushButton *m_maxBtn;
    APushButton *m_normalBtn;
    APushButton *m_closeBtn;
    APushButton *m_minMacBtn;
    APushButton *m_maxMacBtn;
    APushButton *m_normalMacBtn;
    APushButton *m_closeMacBtn;
    QWidget *m_contentWidget;
};
