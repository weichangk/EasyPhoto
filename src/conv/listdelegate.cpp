#include "conv/listdelegate.h"
#include "conv/definerect.h"
#include "core/painter.h"
#include "core/object.h"
#include "widget/listview.h"
#include "types.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>
#include <QComboBox>
#include <QApplication>
#include <QTimer>
#include <QListView>

using namespace QtmCore;
using namespace QtmWidget;

QString conversionOutputFormatComboBoxStyle = R"(
    QComboBox#conversionOutputFormatComboBox
    {
        font-weight: 400;
        font-size: 12px;
        line-height: 16px;
        color:#FFFFFF;
        background: #202031;
        border: 1px solid #39394c;
        padding-left:4px;
        border-radius: 12px;
    }

    QComboBox#conversionOutputFormatComboBox:editable {
        background: transparent;
    }

    QComboBox#conversionOutputFormatComboBox:!editable {
        background: transparent;
    }

    QComboBox#conversionOutputFormatComboBox:hover
    {
        background: #2c2c3f;
        border: 1px solid #505065;
    }

    QComboBox#conversionOutputFormatComboBox:disabled
    {
        background: #202031;
    }

    QComboBox#conversionOutputFormatComboBox:on
    {
        border: 2px solid #986efa;
    }

    QComboBox#conversionOutputFormatComboBox::drop-down{
        subcontrol-position: right center;
        subcontrol-origin: padding;
        width: 16px;
        height: 16px;
        padding-right: 4px;
        background:transparent; 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow
    {
        width: 16px;
        height: 16px;
        subcontrol-origin: content;
        image: url(:/QtmImg/img/dark/v16/icon16/icon16_add.svg); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:on
    {
        image: url(:/QtmImg/img/dark/v16/icon16/icon16_add.svg); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:hover
    {
        image: url(:/QtmImg/img/dark/v16/icon16/icon16_add.svg); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:pressed
    {
        image: url(:/QtmImg/img/dark/v16/icon16/icon16_add.svg); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:disabled
    {
        image: url(:/QtmImg/img/dark/v16/icon16/icon16_add.svg); 
    }

    QComboBox#conversionOutputFormatComboBox QAbstractItemView{
        selection-background-color: #473e6a;
        font-weight: 400;
        font-size: 12px;
        line-height: 16px;
        background-color: #202031;
        border: 1px solid #575766;
        border-radius:0px;
        outline:none;
        color: rgba(255, 255, 255, 0.72);
    }

    QComboBox#conversionOutputFormatComboBox QAbstractItemView::item{
        font-weight: 400;
        font-size: 12px;
        line-height: 16px;
        color:#FFFFFF;
        min-height:24px;
        border:0px;
        padding-left:0px;
    }

    QComboBox#conversionOutputFormatComboBox QAbstractItemView::item:hover {
        background: #352c52;
    }

    QComboBox#conversionOutputFormatComboBox QAbstractItemView::item:selected {
        background: #473e6a;
    }

    QComboBox#conversionOutputFormatComboBox QAbstractItemView::item:checked {
        background: #473e6a;
    }

    QComboBox#conversionOutputFormatComboBox QAbstractItemView::indicator{
        margin-left: 0px;
        width: 16px;
        height: 16px;
        image:url("");
    }

    QComboBox#conversionOutputFormatComboBox QAbstractItemView::indicator:checked
    {
        image: url(:/QtmImg/img/dark/v16/icon16/icon16_add.svg); 
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::vertical
    {
        width:6px;
        margin:0px,4px,6px,4px;
        padding-top:4px; 
        padding-bottom:0px;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::handle:vertical
    {
        width:6px;
        background:rgba(255, 255, 255, 0.24);
        border-radius:3px;
        max-height:34;
        min-height:34;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::handle:vertical:hover
    {
        width:6px;
        background:rgba(255, 255, 255, 0.48);
        border-radius:3px;
        max-height:34;
        min-height:34;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::add-line:vertical 
    {
        height:0px;width:4px;
        subcontrol-position:bottom;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::sub-line:vertical 
    {
        height:0px;width:4px;
        subcontrol-position:top;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::add-page:vertical,QComboBox#conversionOutputFormatComboBox QScrollBar::sub-page:vertical   
    {
        background:transparent;
        border-radius:3px;
    }
)";

ConvListDelegate::ConvListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

QWidget *ConvListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SImageData>();
    m_editingIndex = index;
    QComboBox *editor = new QComboBox(parent);
    editor->setObjectName("conversionOutputFormatComboBox");
    editor->setStyleSheet(conversionOutputFormatComboBoxStyle);
    editor->addItems(CONV_OUTPUT_FORMATS.values());

    blockSignalsFunc(editor, [&]() {
        editor->setCurrentText(data.output_format.toUpper());
    });

    if (index == m_popupComboIndex) {
        QTimer::singleShot(0, editor, [editor]() {
            editor->showPopup();
        });
    }

    connect(editor, &QComboBox::currentTextChanged, this,
            [model = const_cast<QAbstractItemModel *>(index.model()), index, this](const QString &text) {
                auto data = index.data(Qt::UserRole).value<SImageData>();
                data.output_format = text.toLower();
                ListViewModel<SImageData> *md = dynamic_cast<ListViewModel<SImageData> *>(model);
                md->changeData(index.row(), data);
                m_editingIndex = QModelIndex();
                emit const_cast<ConvListDelegate*>(this)->sigUpdateData(data);
            });

    return editor;
}

void ConvListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SImageData>();
    QComboBox *combo = qobject_cast<QComboBox *>(editor);
    QString value = data.output_format.toUpper();
    int idx = combo->findText(value);
    if (idx >= 0)
        combo->setCurrentIndex(idx);
}

void ConvListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    // QComboBox *combo = qobject_cast<QComboBox *>(editor);
    // auto data = index.data(Qt::UserRole).value<SImageData>();
    // data.output_format = combo->currentText().toLower();
    // ListViewModel<SImageData>* md = dynamic_cast<ListViewModel<SImageData>*>(model);
    // md->changeData(index.row(), data);
    m_editingIndex = QModelIndex();
    m_popupComboIndex = QModelIndex();
    QStyledItemDelegate::setModelData(editor, model, index);
}

void ConvListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto comboRect = convListComboRect(option.rect);
    editor->setGeometry(comboRect);
}

bool ConvListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QPoint pos = mouseEvent->pos();
        auto comboRect = convListComboRect(option.rect);
        if (comboRect.contains(pos)) {
            m_popupComboIndex = index;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void ConvListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SImageData>();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;
    bool checked = data.is_checked;

    auto bgRect = rc.adjusted(0, 0, 0, 0);
    int radius = 0;
    // QColor bgColor = QColor("#2a2a3c");
    // if (hover) {
    //     bgColor = QColor("#2d2741");
    // }
    QColor bgColor = QColor("#1a1627");
    // if (hover) {
    //     bgColor = QColor("#2d2741");
    // }
    // if(checked) {
    //     bgColor = QColor("#202031");
    // }

    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    // if (!m_bIsListMode) {
    //     auto pixmapRect = rc.adjusted(4, 24 + 8, -12, -12);
    //     Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, radius, true);
    // }

    // QColor borderColor = QColor("#2a2a3c");
    // if (hover) {
    //     borderColor = QColor("#703eff");
    // }
    // QPen borderPen(borderColor);
    // painter->setPen(borderPen);
    // painter->drawRoundedRect(bgRect.adjusted(1, 1, -1, -1), radius, radius);
    // painter->setPen(Qt::NoPen);

    auto checkedRect = convListCheckedRect(bgRect);
    if (data.is_checked) {
        QColor checkBgColor = QColor("#a070ff");
        if (checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBgColor = QColor("#ad84ff");
            }
            if (pressed) {
                checkBgColor = QColor("#bb99ff");
            }
        }
        painter->setBrush(checkBgColor);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setBrush(Qt::NoBrush);
        Painter::paintPixmap(painter, checkedRect, data.checked_icon, 1, 0, true);
    } else {
        QColor checkBgColor = QColor("#2f2f36");
        if (checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBgColor = QColor("#3a3a43");
            }
            if (pressed) {
                checkBgColor = QColor("#464650");
            }
        }
        painter->setBrush(checkBgColor);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setBrush(Qt::NoBrush);
        QColor checkBorderColor = QColor("#575766");
        QPen pen(checkBorderColor);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setPen(Qt::NoPen);
    }

    auto delRect = convListDelRect(bgRect);
    QColor delBgColor = QColor("#fa7681");
    if (delRect.contains(m_CurPos)) {
        if (hover) {
            delBgColor.setAlpha(200);
        }
        if (pressed) {
            delBgColor.setAlpha(100);
        }
    }
    if (hover || pressed) {
        painter->setBrush(delBgColor);
        painter->drawRoundedRect(delRect, 8, 8);
        painter->setBrush(Qt::NoBrush);
        Painter::paintPixmap(painter, delRect, data.delete_icon, 1, 0, true);
    }

    auto nameRect = convListNameRect(bgRect);
    QColor nameColor = QColor("#ffffff");
    QPen penName(nameColor);
    painter->setPen(penName);
    QFont fontName = painter->font();
    fontName.setPixelSize(12);
    painter->setFont(fontName);
    QString fileName = data.file_name;
    QFontMetricsF fileMetrics(fontName);
    if (fileMetrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = fileMetrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width());
    }
    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, fileName);

    auto resolutionRect = convListResolutionRect(bgRect);
    painter->drawText(resolutionRect, Qt::AlignLeft | Qt::AlignVCenter, QString("%1x%2").arg(data.resolution.width()).arg(data.resolution.height()));

    painter->setPen(Qt::NoPen);

    if (index != m_editingIndex) {
        auto comboRect = convListComboRect(bgRect);
        int comboRadius = 12;
        QColor comboBgColor = QColor("#1a1627");
        if(hover) {
            comboBgColor = QColor("#2c2c3f");
        }
        painter->setBrush(comboBgColor);
        painter->drawRoundedRect(comboRect, comboRadius, comboRadius);
        painter->setBrush(Qt::NoBrush);

        QColor comboBorderColor = QColor("#39394c");
        QPen comboBorderPen(comboBorderColor);
        painter->setPen(comboBorderPen);
        painter->drawRoundedRect(comboRect.adjusted(1, 1, -1, -1), comboRadius, comboRadius);
        painter->setPen(Qt::NoPen);

        auto comboTextRect = QRect(comboRect.left() + 5, comboRect.y(), comboRect.width() - 24, comboRect.height());
        QColor comboTextColor = QColor("#ffffff");
        QPen comboTextPen(comboTextColor);
        painter->setPen(comboTextPen);
        QFont comboTextFont = painter->font();
        comboTextFont.setPixelSize(12);
        painter->setFont(comboTextFont);
        QString comboText = data.output_format.toUpper();
        painter->drawText(comboTextRect, Qt::AlignLeft | Qt::AlignVCenter, comboText);
        painter->setPen(Qt::NoPen);

        QStyleOption arrowOpt;
        arrowOpt.rect = QRect(comboRect.right() - 16, comboRect.y() + 6, 12, 12);
        arrowOpt.state = QStyle::State_Enabled;
        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorArrowDown, &arrowOpt, painter);
    }

    auto stateRect = convListStateRect(bgRect);
    Painter::paintPixmap(painter, stateRect, data.state_icons[data.state], 1, 0, true);

    auto convRect = convListConvRect(bgRect);
    int convRadius = 10;
    QColor convBgColor = QColor("#2c2c3f");
    if(hover) {
        convBgColor = QColor("#433767");
    }
    if(pressed) {
        convBgColor = QColor("#2f2b47");
    }
    painter->setBrush(convBgColor);
    painter->drawRoundedRect(convRect, convRadius, convRadius);
    painter->setBrush(Qt::NoBrush);

    QColor convBorderColor = QColor("#a070ff");
    QPen convBorderPen(convBorderColor);
    painter->setPen(convBorderPen);
    painter->drawRoundedRect(convRect.adjusted(1, 1, -1, -1), convRadius, convRadius);
    painter->setPen(Qt::NoPen);

    auto convTextRect = convRect;
    QColor convTextColor = QColor("#ffffff");
    QPen convTextPen(convTextColor);
    painter->setPen(convTextPen);
    QFont convTextFont = painter->font();
    convTextFont.setPixelSize(12);
    painter->setFont(convTextFont);
    QString convText = tr("Convert");
    painter->drawText(convTextRect, Qt::AlignCenter, convText);
    painter->setPen(Qt::NoPen);
}

bool ConvListDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseMove || type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        m_EventType = type;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint pos = mouseEvent->pos();
            m_CurPos = pos;
            QWidget *curWidget = static_cast<QWidget *>(object);
            curWidget->update();
            if(type == QEvent::MouseButtonPress)
            {
                // 使用了 Editor 后， QListView::clicked 信号第一次点击不生效，点击信号改为这里触发
                QListView *view = static_cast<QListView *>(this->parent());
                QModelIndex index = view->indexAt(pos);
                sigClicked(index);
            }
        }
    }
    return QStyledItemDelegate::eventFilter(object, event);
}

QSize ConvListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (m_bIsListMode) {
        QWidget *parent = static_cast<QWidget *>(this->parent());
        // return QSize(parent->width() - 10, n_ListItemHeight);
        return QSize(parent->width(), n_ListItemHeight);
    }
    return m_Size;
}

void ConvListDelegate::setListMode(bool b) {
    m_bIsListMode = b;
}

bool ConvListDelegate::isListMode() const {
    return m_bIsListMode;
}