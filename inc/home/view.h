#pragma once
#include "globalview.h"
#include "mvp/view.h"

// #include <QStyledItemDelegate>
// #include <QEvent>

using namespace qtmaterialmvp;

// class HomeFuncItemDelegate : public QStyledItemDelegate {
//     Q_OBJECT
// public:
//     explicit HomeFuncItemDelegate(QObject *parent);
//     void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//     bool eventFilter(QObject *object, QEvent *event) override;
//     QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

// private:
//     QSize m_Size = QSize(60 + 8, 40 + 8);
//     int m_nEventType = QEvent::None;
//     QPoint m_CurPos;
// };

class HomeView : public QWidget, public View {
    Q_OBJECT
public:
    explicit HomeView(QWidget *parent = nullptr);
    ~HomeView() override {
    }

private:
    void createUi();
    void connectSig();
};