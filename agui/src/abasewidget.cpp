/*
 * @Author: weick
 * @Date: 2023-12-05 22:54:43
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:54:43
 */

#include "inc/abasewidget.h"
#include <QEvent>

ABaseWidget::ABaseWidget(QWidget *parent) :
    AWidget(parent) {
}

ABaseWidget::~ABaseWidget() {
}

bool ABaseWidget::event(QEvent *e) {
    if (e->type() == QEvent::LanguageChange) {
        changeLanguage();
    }
    return AWidget::event(e);
}
