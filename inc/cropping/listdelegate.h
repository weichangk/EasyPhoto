#pragma once
#include <QStyledItemDelegate>
#include <QEvent>

class CroppingListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit CroppingListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize m_Size = QSize(208 + 8, 200 + 8);
    int m_EventType = QEvent::None;
    QPoint m_CurPos;
};