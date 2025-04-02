#pragma once
#include <QStyledItemDelegate>
#include <QEvent>

class EnhanceModelListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit EnhanceModelListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize m_Size = QSize(140, 108);
    int m_EventType = QEvent::None;
    QPoint m_CurPos;
};