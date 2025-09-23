#pragma once
#include <QStyledItemDelegate>
#include <QEvent>

class CompListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit CompListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setListMode(bool b);
    bool isListMode() const;

private:
    QSize m_Size = QSize(200 + 8, 200 + 8);
    int m_EventType = QEvent::None;
    QPoint m_CurPos;
    bool m_bIsListMode = true;
    int n_ListItemHeight = 24 + 8;
};