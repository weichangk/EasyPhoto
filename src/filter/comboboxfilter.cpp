#include "filter/comboboxfilter.h"
#include <QEvent>

ComboBoxFilter::ComboBoxFilter(QObject *parent) :
    QObject(parent) {
}

bool ComboBoxFilter::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        emit sigClicked();
    }
    return QObject::eventFilter(watched, event);
}