/*
 * @Author: weick
 * @Date: 2023-12-10 23:24:02
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 00:00:29
 */

#pragma once
#include <QStyledItemDelegate>
#include <QEvent>

class ConversionListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ConversionListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void changeSizeHint(const QSize &size);

private:
    QSize m_Size = QSize(130, 130);
    int m_EventType = QEvent::None;
    QPoint m_CurPos;
};
