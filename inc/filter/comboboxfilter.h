#pragma once
#include <QObject>

class ComboBoxFilter : public QObject {
    Q_OBJECT
public:
    explicit ComboBoxFilter(QObject *parent = nullptr);

Q_SIGNALS:
    void sigClicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};