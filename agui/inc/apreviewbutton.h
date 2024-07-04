/*
 * @Author: weick
 * @Date: 2024-07-02 07:23:58
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-02 07:55:56
 */

#pragma once
#include "agui_global.h"
#include "../awidget/inc/awidget.h"

class AGUI_EXPORT APreviewButton : public AWidget {
    Q_OBJECT
    Q_PROPERTY(QPixmap normalIcon READ normalIcon WRITE setNormalIcon NOTIFY sigNormalIconChanged)
    Q_PROPERTY(QPixmap hoverIcon READ hoverIcon WRITE setHoverIcon NOTIFY sigHoverIconChanged)
    Q_PROPERTY(QPixmap pressedIcon READ pressedIcon WRITE setPressedIcon NOTIFY sigPressedIconChanged)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY sigIconSizeChanged)

public:
    enum IconState {
        kNormal,
        kHover,
        kPressed
    };

    explicit APreviewButton(QWidget *parent = nullptr);
    ~APreviewButton();

    QPixmap &normalIcon();
    void setNormalIcon(const QPixmap &icon);
    QPixmap &hoverIcon();
    void setHoverIcon(const QPixmap &icon);
    QPixmap &pressedIcon();
    void setPressedIcon(const QPixmap &icon);
    QSize &iconSize();
    void setIconSize(const QSize &size);

Q_SIGNALS:
    void sigClicked();
    void sigNormalIconChanged(const QPixmap &icon);
    void sigHoverIconChanged(const QPixmap &icon);
    void sigPressedIconChanged(const QPixmap &icon);
    void sigIconSizeChanged(const QSize &size);
    
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void changeEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    IconState icon_state_ = kNormal;
    QPixmap normal_icon_;
    QPixmap hover_icon_;
    QPixmap pressed_icon_;
    QSize icon_size_;
};