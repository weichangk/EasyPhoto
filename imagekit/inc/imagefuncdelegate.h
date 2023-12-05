/*
 * @Author: weick
 * @Date: 2023-12-05 23:01:31
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:01:31
 */

#pragma once
#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>

class ImageFuncDelegate : public QItemDelegate {
    Q_OBJECT
public:
    ImageFuncDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize m_Size = QSize(0, 0);
};
