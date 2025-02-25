#pragma once
#include "globalview.h"

#include <QStyledItemDelegate>
#include <QEvent>

class FuncItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit FuncItemDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize m_Size = QSize(234, 210);
    int m_nEventType = QEvent::None;
    QPoint m_CurPos;
};