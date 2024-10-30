#pragma once
#include <QStyledItemDelegate>
#include <QEvent>

namespace imageconversion {
class ConversionListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ConversionListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void changeSizeHint(const QSize &size);

private:
    QSize m_Size = QSize(176 + 8, 176 + 8); // 间距8
    int m_EventType = QEvent::None;
    QPoint m_CurPos;
};
} // namespace imageconversion