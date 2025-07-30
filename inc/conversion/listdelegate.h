#pragma once
#include "model.h"

#include <QStyledItemDelegate>
#include <QEvent>

class ConversionListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ConversionListDelegate(QObject *parent);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setListMode(bool b);
    bool isListMode() const;

Q_SIGNALS:
    void sigUpdateData(const SConversionData &data);
    void sigClicked(const QModelIndex &index);

private:
    QSize m_Size = QSize(208 + 8, 200 + 8);
    int m_EventType = QEvent::None;
    QPoint m_CurPos;
    bool m_bIsListMode = true;
    int n_ListItemHeight = 24 + 8;
    mutable QModelIndex m_editingIndex;
    mutable QModelIndex m_popupComboIndex;
};