#pragma once
#include <QStyledItemDelegate>
#include <QEvent>

class ConversionOutputFormatDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ConversionOutputFormatDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize m_Size = QSize(60 + 8, 40 + 8);
    int m_nEventType = QEvent::None;
    QPoint m_CurPos;
};