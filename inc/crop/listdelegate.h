#pragma once
#include <QStyledItemDelegate>
#include <QEvent>

class ScalelListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ScalelListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize m_Size = QSize(72, 56);
    int m_EventType = QEvent::None;
    QPoint m_CurPos;
};