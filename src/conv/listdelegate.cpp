#include "conv/listdelegate.h"
#include "conv/definerect.h"
#include "core/painter.h"
#include "core/object.h"
#include "core/theme.h"
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

QString conversionOutputFormatComboBoxStyle_dark = R"(
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
        width: 20px;
        height: 20px;
        padding-right: 0px;
        background:transparent; 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow
    {
        width: 20px;
        height: 20px;
        subcontrol-origin: content;
        image: url(:/QtmImg/img/dark/icon/icon_basic/icon20/icon20_Arrow_down_white_n.png); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:on
    {
        image: url(:/QtmImg/img/dark/icon/icon_basic/icon20/icon20_Arrow_down_h.png); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:hover
    {
        image: url(:/QtmImg/img/dark/icon/icon_basic/icon20/icon20_Arrow_down_h.png); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:pressed
    {
        image: url(:/QtmImg/img/dark/icon/icon_basic/icon20/icon20_Arrow_down_h.png); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:disabled
    {
        image: url(:/QtmImg/img/dark/icon/icon_basic/icon20/icon20_Arrow_down_d.png); 
    }

    QComboBox#conversionOutputFormatComboBox QAbstractItemView{
        selection-background-color: #473e6a;
		selection-color: #FFFFFF;
        font-weight: 400;
        font-size: 12px;
        line-height: 16px;
        background-color: #202031;
        border: 1px solid #575766;
        border-radius:0px;
        outline:none;
        color: rgba(255, 255, 255, 0.72);
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::vertical
    {
        width:4px;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::handle:vertical
    {
        background:rgba(255, 255, 255, 0.24);
        border-radius:2px;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::handle:vertical:hover
    {
        background:rgba(255, 255, 255, 0.48);
    }
)";

QString conversionOutputFormatComboBoxStyle_light = R"(
    QComboBox#conversionOutputFormatComboBox
    {
        font-weight: 400;
        font-size: 12px;
        line-height: 16px;
        color:#000000;
        background: transparent;
        border: 1px solid #e4e8f0;
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
        background: transparent;
        border: 1px solid #e4e8f0;
    }

    QComboBox#conversionOutputFormatComboBox:disabled
    {
        background: transparent;
    }

    QComboBox#conversionOutputFormatComboBox:on
    {
        border: 2px solid #986efa;
    }

    QComboBox#conversionOutputFormatComboBox::drop-down{
        subcontrol-position: right center;
        subcontrol-origin: padding;
        width: 20px;
        height: 20px;
        padding-right: 0px;
        background:transparent; 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow
    {
        width: 20px;
        height: 20px;
        subcontrol-origin: content;
        image: url(:/QtmImg/img/light/icon/icon_basic/icon20/icon20_Arrow_down_black_n.png); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:on
    {
        image: url(:/QtmImg/img/light/icon/icon_basic/icon20/icon20_Arrow_down_h.png); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:hover
    {
        image: url(:/QtmImg/img/light/icon/icon_basic/icon20/icon20_Arrow_down_h.png); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:pressed
    {
        image: url(:/QtmImg/img/light/icon/icon_basic/icon20/icon20_Arrow_down_h.png); 
    }

    QComboBox#conversionOutputFormatComboBox::down-arrow:disabled
    {
        image: url(:/QtmImg/img/light/icon/icon_basic/icon20/icon20_Arrow_down_d.png); 
    }

    QComboBox#conversionOutputFormatComboBox QAbstractItemView{
        selection-background-color: #f4f6f9;
        selection-color: #000000;
        font-weight: 400;
        font-size: 12px;
        line-height: 16px;
        background-color: #ffffff;
        border: 1px solid #e4e8f0;
        border-radius:0px;
        outline:none;
        color: #000000;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::vertical
    {
        width:4px;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::handle:vertical
    {
        background:#e4e8f0;
        border-radius:2px;
    }

    QComboBox#conversionOutputFormatComboBox QScrollBar::handle:vertical:hover
    {
        background:#d9deea;
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
    if(QtmCore::Theme::currentTheme() == "dark")
        editor->setStyleSheet(conversionOutputFormatComboBoxStyle_dark);
    else
        editor->setStyleSheet(conversionOutputFormatComboBoxStyle_light);
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
    QColor bgColor = Qt::transparent;

    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    auto checkedRect = convListCheckedRect(bgRect);
    if (data.is_checked) {
        QColor checkBgColor = QColor(QtmCore::Theme::colors().value("color4"));
        if (checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBgColor.setAlphaF(0.9);
            }
            if (pressed) {
                checkBgColor.setAlphaF(0.8);
            }
        }
        painter->setBrush(checkBgColor);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setBrush(Qt::NoBrush);
        Painter::paintPixmap(painter, checkedRect, data.checked_icon, 1, 0, true);
    } else {
        QColor checkBgColor = QColor(QtmCore::Theme::bgColors().value("color2"));
        if (checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBgColor.setAlphaF(0.9);
            }
            if (pressed) {
                checkBgColor.setAlphaF(0.8);
            }
        }
        painter->setBrush(checkBgColor);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setBrush(Qt::NoBrush);
        QColor checkBorderColor = QColor(QtmCore::Theme::bdColors().value("color3"));
        if (checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBorderColor.setAlphaF(0.9);
            }
            if (pressed) {
                checkBorderColor.setAlphaF(0.8);
            }
        }
        QPen pen(checkBorderColor);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setPen(Qt::NoPen);
    }

    auto delRect = convListDelRect(bgRect);
    QColor delBgColor = QColor(QtmCore::Theme::colors().value("color5"));
    if (delRect.contains(m_CurPos)) {
        if (hover) {
            delBgColor.setAlphaF(0.9);
        }
        if (pressed) {
            delBgColor.setAlphaF(0.8);
        }
    }
    if (hover || pressed) {
        painter->setBrush(delBgColor);
        painter->drawRoundedRect(delRect, 8, 8);
        painter->setBrush(Qt::NoBrush);
        Painter::paintPixmap(painter, delRect, data.delete_icon, 1, 0, true);
    }

    auto nameRect = convListNameRect(bgRect);
    QColor nameColor = QColor(QtmCore::Theme::foreColors().value("color0"));
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
        QColor comboBgColor = Qt::transparent;
        painter->setBrush(comboBgColor);
        painter->drawRoundedRect(comboRect, comboRadius, comboRadius);
        painter->setBrush(Qt::NoBrush);

        QColor comboBorderColor = QColor(QtmCore::Theme::bdColors().value("color2"));
        QPen comboBorderPen(comboBorderColor);
        painter->setPen(comboBorderPen);
        painter->drawRoundedRect(comboRect.adjusted(1, 1, -1, -1), comboRadius, comboRadius);
        painter->setPen(Qt::NoPen);

        auto comboTextRect = QRect(comboRect.left() + 5, comboRect.y(), comboRect.width() - 24, comboRect.height());
        QColor comboTextColor = QColor(QtmCore::Theme::foreColors().value("color0"));
        QPen comboTextPen(comboTextColor);
        painter->setPen(comboTextPen);
        QFont comboTextFont = painter->font();
        comboTextFont.setPixelSize(12);
        painter->setFont(comboTextFont);
        QString comboText = data.output_format.toUpper();
        painter->drawText(comboTextRect, Qt::AlignLeft | Qt::AlignVCenter, comboText);
        painter->setPen(Qt::NoPen);

        QRect arrowRect(comboRect.right() - 20, comboRect.y() + 2, 20, 20);
        QPixmap arrowPixmap(":/QtmImg/img/light/icon/icon_basic/icon20/icon20_Arrow_down_black_n.png");
        if(QtmCore::Theme::currentTheme() == "dark")
        {
            QPixmap arrowPixmap(":/QtmImg/img/dack/icon/icon_basic/icon20/icon20_Arrow_down_white_n.png");
        }
        painter->drawPixmap(arrowRect, arrowPixmap);
    }

    auto stateRect = convListStateRect(bgRect);
    Painter::paintPixmap(painter, stateRect, data.state_icons[data.state], 1, 0, true);

    auto convRect = convListConvRect(bgRect);
    int convRadius = 12;
    QColor convBgColor = Qt::transparent;
    painter->setBrush(convBgColor);
    painter->drawRoundedRect(convRect, convRadius, convRadius);
    painter->setBrush(Qt::NoBrush);

    QColor convBorderColor = QColor(QtmCore::Theme::colors().value("color3"));
    QPen convBorderPen(convBorderColor);
    painter->setPen(convBorderPen);
    painter->drawRoundedRect(convRect.adjusted(1, 1, -1, -1), convRadius, convRadius);
    painter->setPen(Qt::NoPen);

    auto convTextRect = convRect;
    QColor convTextColor = QColor(QtmCore::Theme::foreColors().value("color0"));
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