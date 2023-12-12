/*
 * @Author: weick
 * @Date: 2023-12-13 00:09:55
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 00:14:57
 */

#pragma once
#include <QListView>

class ConversionListView : public QListView {
    Q_OBJECT
public:
    explicit ConversionListView(QWidget *parent = 0);
};

ConversionListView::ConversionListView(QWidget *parent) :
    QListView(parent) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAttribute(Qt::WA_StyledBackground);

}
