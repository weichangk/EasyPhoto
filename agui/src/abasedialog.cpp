/*
 * @Author: weick
 * @Date: 2024-07-06 14:36:58
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-06 14:39:10
 */

#include "inc/abasedialog.h"
#include <QEvent>

ABaseDialog::ABaseDialog(QDialog *parent) :
    ADialog(parent) {
}

ABaseDialog::~ABaseDialog() {
}

bool ABaseDialog::event(QEvent *e) {
    if (e->type() == QEvent::LanguageChange) {
        changeLanguage();
    }
    return ADialog::event(e);
}
